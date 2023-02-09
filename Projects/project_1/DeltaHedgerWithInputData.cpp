//
// Created by Roy Makkar Gabriel on 10/12/22.
//

#include "DeltaHedgerWithInputData.h"
#include "StdNormalCDF.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <random>
#include <iostream>
#include <utility>

using namespace std;

// Default Constructor
DeltaHedgerWithInput::DeltaHedgerWithInput() {}


// Default Constructor with parameters
DeltaHedgerWithInput::DeltaHedgerWithInput(string t_0, string t_N, string exp_date, double Strike) {
    // Initialize the necessary variables and functions when class is called
    start_date = std::move(t_0);
    end_date = std::move(t_N);
    expiration_date = std::move(exp_date);
    K = Strike;
    read_option();
    get_IV();
    get_Delta();
    get_PNL();
    get_HE();
    to_csv();
}

// Gets corresponding value from a vector based on the index of another vector
double get_match(vector<double> rate_vec, vector<string> date_vec, string date)
{
// code for finding the financial value for the
// given date and returning the matching value for that month
    for (int i = 0; i < date_vec.size(); ++i) {
        if (date == date_vec[i]){
            return rate_vec[i];
        }
    }
    return -1;
}

// Reads data in given csv files (interest rate data -> interest.csv)
pair<vector<string>, vector<double>> read_ir() {
    // define variable types
    vector<string> date_vec;
    vector<double> rate_vec;
    string line, str1, str2;
    pair<vector<string>, vector<double>> output;

    // read interest rate csv file
    ifstream infile("../interest.csv");
    if (infile.fail()) {
        cout << "File Not Found! Please make sure the path is define correctly or that you are in the right"
                "directory!" << endl;
    }

    getline(infile, line);
    while (!infile.fail()) {
        getline(infile, line);
        stringstream linestream(line);
        if (!linestream.str().empty()) {
            getline(linestream, str1, ',');
            date_vec.push_back(str1);
            getline(linestream, str2, ',');
            rate_vec.push_back(stod(str2) / 100);
        }
    }

    infile.close();
    output.first = date_vec;
    output.second = rate_vec;
    return output;
}

// Reads data in given csv files (GOOG adjusted close prices -> sec_GOOG.csv)
pair<vector<string>, vector<double>> read_stock() {
    // Define variable types
    vector<string> date_vec;
    vector<double> price_vec;
    string line, str1, str2;
    pair<vector<string>, vector<double>> output;

    // Read GOOG stock adjusted close price csv file
    ifstream infile("../sec_GOOG.csv");
    if (infile.fail()) {
        cout << "File Not Found! Please make sure the path is define correctly or that you are in the right"
                "directory!" << endl;
    }

    getline(infile, line);
    while (!infile.fail()) {
        getline(infile, line);
        stringstream linestream(line);
        if (!linestream.str().empty()) {
            getline(linestream, str1, ',');
            date_vec.push_back(str1);
            getline(linestream, str2, ',');
            price_vec.push_back(stod(str2));
        }
    }
    output.first = date_vec;
    output.second = price_vec;
    return output;
}

// Reads data in given csv files (GOOG option bid-ask data -> op_GOOG.csv) and combine other csv files
vector<Option> DeltaHedgerWithInput::read_option() {
    // Define variable types
    vector<Option> option_vec;
    vector<string> date_vec_ir, date_vec_price;
    vector<double> rate_vec, price_vec;
    string line, t_0, t_N, F, Strike, Bid, Ask;
    double OP, Spot, rf;
    pair<vector<string>, vector<double>> temp_data;

    // get interest rate csv file data
    temp_data = read_ir();
    date_vec_ir = temp_data.first;
    rate_vec = temp_data.second;

    // get stock price csv file data
    temp_data = read_stock();
    date_vec_price = temp_data.first;
    price_vec = temp_data.second;

    // Read GOOG Option csv file
    ifstream infile("../op_GOOG.csv");
    if (infile.fail()) {
        cout << "File Not Found! Please make sure the path is define correctly or that you are in the right"
                "directory!" << endl;
    }

    // read each line item and create option instances stored in the option vector
    getline(infile, line);
    while (!infile.fail()) {
        getline(infile, line);
        stringstream linestream(line);
        if (linestream.str() != "") {
            getline(linestream, t_0, ',');
            getline(linestream, t_N, ',');
            getline(linestream, F, ',');
            getline(linestream, Strike, ',');
            getline(linestream, Bid, ',');
            getline(linestream, Ask, ',');

            if (t_N == expiration_date && stod(Strike) == K && F == "C") {
                OP = (stod(Bid) + stod(Ask)) / 2;
                Spot = get_match(price_vec, date_vec_price, t_0);
                rf = get_match(rate_vec, date_vec_ir, t_0);
                auto *f = reinterpret_cast<string *>(&F[0]);

                Option temp_option = Option(stod(Strike), Spot, OP, rf, *f, t_0, t_N);
                option_vec.push_back(temp_option);
            }
        }
    }

    int i_0 = 0;
    int i_N = 0;
    for (int i = 0; i < option_vec.size(); i++) {
        if (option_vec[i].get_t_0() == start_date) {
            i_0 = i;
        }
        if (option_vec[i].get_t_0() == end_date) {
            i_N = i + 1;
        }
    }
    vector<Option> Final_Option(&option_vec[i_0], &option_vec[i_N]);
    option_array = Final_Option;
    return Final_Option;
}

// Calculate Implied volatility
vector<double> DeltaHedgerWithInput::get_IV() {

    // Define variable types
    vector<double> iv, vol_vec;
    double temp_min, temp_vol, temp_OP;

    // Append to volatility vector range of values
    for (double s = 0.01; s <= 0.99; s = s + 0.001) {
        vol_vec.push_back(s);
    }

    for (auto temp_option : option_array) {
        temp_min = 999999; // initialize with large value for dynamic updating
        for (double j : vol_vec) {
            temp_OP = temp_option.BSM_Pricer(j);
            if (abs(temp_option.get_OP() - temp_OP) < temp_min) {
                temp_vol = j;
                temp_min = abs(temp_option.get_OP() - temp_OP);
            }
        }
        iv.push_back(temp_vol);
    }
    ivol_vec = iv;
    return iv;
}

// Calculate Delta
vector<double> DeltaHedgerWithInput::get_Delta() {

    // Define variable types
    vector<double> d_vec;
    double temp_delta, temp_T, sqrt_T, d1, Nd1;
    string F;

    // Iterate and store delta values in order to hedge later
    for (int i = 0; i < option_array.size(); i++) {
        temp_delta = 0;
        Option temp_option = option_array[i];

        temp_T = temp_option.get_T(temp_option.get_t_0(), temp_option.get_t_N()) / 252;
        sqrt_T = sqrt(temp_T);

        d1 = (log(temp_option.get_S() / temp_option.get_K()) +
                (temp_option.get_r() + 0.5 * pow(ivol_vec[i], 2)) * temp_T) /
                (ivol_vec[i] * sqrt_T);
        Nd1 = StdNormalCDF::CDF(d1);
        F = temp_option.get_flag();

        if (F == "C" || F == "c") {
            temp_delta = Nd1;
        }
        else if (F == "P" || F == "p") {
            temp_delta = Nd1 - 1;
        }
        d_vec.push_back(temp_delta);
    }
    delta_vec = d_vec;
    return d_vec;
}

// Calculate Hedging Error
vector<double> DeltaHedgerWithInput::get_HE() {

    // Define variable types
    vector<double> B_vec, HE_vec;
    double temp_B, HE;

    // Apply the Cumulative Hedging Error Formula till t_i
    // First Calculate B_i
    for (int i = 0; i < option_array.size(); i++) {
        if (i == 0) {
            temp_B = option_array[i].get_OP() - delta_vec[i] * option_array[i].get_S();
        }
        else {
            temp_B = (delta_vec[i - 1] - delta_vec[i]) * option_array[i].get_S() +
                    B_vec[i - 1] * exp(option_array[i].get_r() / 252);
        }
        B_vec.push_back(temp_B);
    }

    // Second Calculate HE
    for (int i = 0; i < option_array.size(); i++) {
        if (i == 0) {
            HE = 0;
        }
        else {
            HE = delta_vec[i - 1] * option_array[i].get_S() +
                 B_vec[i - 1] * exp(option_array[i].get_r() / 252) - option_array[i].get_OP();
        }
        HE_vec.push_back(HE);
    }
    PNL_H_vec = HE_vec;
    return HE_vec;
}

// Calculate PNL
vector<double> DeltaHedgerWithInput::get_PNL() {

    // Define variable types
    vector<double> pnl_vec;
    double temp_pnl;

    for (auto & i : option_array) {
        temp_pnl = option_array[0].get_OP() - i.get_OP();
        pnl_vec.push_back(temp_pnl);
    }
    PNL_vec = pnl_vec;
    return PNL_vec;
}

// Save output to csv file after running above functions
void DeltaHedgerWithInput::to_csv() {
    ofstream output;
    output.open("../output.csv");
    output << "Date" << "," << "Stock Price" << "," << "Option Price" << ","
            << "Implied Volatility" << "," << "Delta" << "," << "PNL" << ","
            << "PNL Hedged" << endl;

    // NOTE: I ignored HE_series vector since HE_series and PNL_H
    // are the same data
    for (int i = 0; i < option_array.size(); i++) {
        Option temp_option = option_array[i];
        output << temp_option.get_t_0() << ","
        << temp_option.get_S() << ","
        << temp_option.get_OP() << ","
        << ivol_vec[i] << "," << delta_vec[i]
        << "," << PNL_vec[i] << ","
        << PNL_H_vec[i] << endl;
    }
    output.close();
}