//
// Created by Roy Makkar Gabriel on 10/10/22.
//

#include "Option.h"
#include "StdNormalCDF.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

// Define init
void Option::init(double Strike, double Spot, double Option_Price, double rfr,
                  string F, string t0, string tN) {
    K = Strike;
    S = Spot;
    r = rfr;
    flag = F;
    t_0 = t0;
    t_N = tN;
    OP = Option_Price;
}


// Constructor with parameters
Option::Option(double Strike, double Spot, double Option_Price, double rfr, string F, string t0, string tN) {
    init(Strike, Spot, Option_Price, rfr, F, t0, tN);
};

// Define get methods
double Option::get_K() const {return K;};
double Option::get_S() const {return S;};
double Option::get_r() const {return r;};
double Option::get_OP() const {return OP;};

double Option::get_T(string start_date, string end_date) {
    // define variable types
    int input_day{0}, input_month{0}, input_year{0};
    tm dt = {0}, dt_start, dt_end;

    // start_date details
    dt = { 0 };

    input_day = std::stoi(start_date.substr(8, 2));
    dt.tm_mday = input_day;

    input_month = std::stoi(start_date.substr(5, 2));
    dt.tm_mon = input_month - 1;

    input_year = std::stoi(start_date.substr(0, 4));
    dt.tm_year = input_year - 1900;

    dt_start = dt;

    // end date details
    input_day = std::stoi(end_date.substr(8, 2));
    dt.tm_mday = input_day;

    input_month = std::stoi(end_date.substr(5, 2));
    dt.tm_mon = input_month - 1;

    input_year = std::stoi(end_date.substr(0, 4));
    dt.tm_year = input_year - 1900;

    dt_end = dt;

    // Convert to time
    time_t time_end = mktime(&dt_end);
    time_t time_start = mktime(&dt_start);

    // Calculate time difference
    double time_diff = static_cast<double>(time_end - time_start) / (60.0 * 60.0 * 24.0);
    if (time_diff == 0) { time_diff += 0.0000001;}
    return time_diff;
};

string Option::get_t_0() const {return t_0;};
string Option::get_t_N() const {return t_N;};
string Option::get_flag() const {return flag;};

// BSM Pricer
double Option::BSM_Pricer(double vol) {
    // initialize variables
    double output, d1, d2, sqrt_T;
    K = Option::get_K();
    S = Option::get_S();
    r = Option::get_r();
    t_0 = get_t_0();
    t_N = get_t_N();
    double T = Option::get_T(t_0, t_N) / 225;

    // Return -1, -2 if incorrect input
    if (K < 0 || S < 0 || T < 0 || r < 0 || vol < 0) {
        cout << "Error! All inputs must be non-negative!" << endl;
        // if incorrect input
        output = -1;
        return output;
    }

    // calculate common constants
    sqrt_T = sqrt(T);
    d1 = (log(S / K) + (r + 0.5 * pow(vol, 2)) * T) / (vol * sqrt_T);
    d2 = d1 - (vol * sqrt_T);

    // calculate option value and delta
    if (flag == "C" or flag == "c") {
        // handle T = 0 edge case
        if (T == 0) {
            output = (S > K) ? S - K : 0;
            return output;
        };

        // Option Value
        output = S * StdNormalCDF::CDF(d1) - K * exp(-r * T) * StdNormalCDF::CDF(d2);

    } else if (flag == "P" or flag == "p") {
        // handle T = 0 edge case
        if (T == 0) {
            output = (S < K) ? K - S : 0;
            return output;
        };
        // Option Value
        output = K * exp(-r * T) * StdNormalCDF::CDF(-d2) - S * StdNormalCDF::CDF(-d1);
    } else {
        cout << "Error! Option type must be one of 'P'/'p' or 'C'/'c'!" << endl;
        // if incorrect input
        output = -1;
    };

    return output;
};

