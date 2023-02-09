//
// Created by Roy Makkar Gabriel on 10/1/22.
//

#include "Option_Price.h"
#include "StdNormalCDF.h"
#include <cmath>
#include <utility>
#include <vector>
#include <string>
using namespace std;

// Initialize flag using constructor
Option_Price::Option_Price() {
    flag = "C";
//    n_intervals = 99;  // increase this number to make the pricer more accurate
};

Option_Price::~Option_Price() = default;

Option_Price::Option_Price(string F, double K, double S, double r, double T, double vol) : Option(K, S, r, T, vol) {
    flag = std::move(F);
//    n_intervals = 99;  // increase this number to make the pricer more accurate
}

std::pair<double, double> Option_Price::BSM_Pricer() {
    // initialize variables
    double K, S, r, T, vol;
    K = Option::get_K();
    S = Option::get_S();
    r = Option::get_r();
    T = Option::get_T();
    vol = Option::get_vol();

    // initialize variable type
    pair<double, double> output;
    double d1, d2, sqrt_T;

    // Return -1, -2 if incorrect input
    if (K < 0 || S < 0 || T < 0 || r < 0 || vol < 0){
        cout << "Error! All inputs must be non-negative!" << endl;
        // if incorrect input
        output.first = -1;
        output.second = -2; // since delta is bounded by -1 and 1 inclusive
        return output;
    }

    // calculate common constants
    sqrt_T = sqrt(T);
    d1 = (log(S / K) + (r + 0.5 * pow(vol, 2)) * T) / (vol * sqrt_T);
    d2 = d1 - (vol * sqrt_T);

    // calculate option value and delta
    if (flag == "C" or flag == "c") {
        // handle T = 0 edge case
        if(T==0){
            output.first = (S > K) ? S - K : 0;
            output.second = 0.5;
            return output;
        };

        // Option Value
        output.first = S * StdNormalCDF::CDF(d1) - K * exp(-r * T) * StdNormalCDF::CDF(d2);
        // Delta
        output.second = StdNormalCDF::CDF(d1);
    } else if (flag == "P" or flag == "p") {
        // handle T = 0 edge case
        if(T==0){
            output.first = (S < K) ? K - S : 0;
            output.second = -0.5;
            return output;
        };
        // Option Value
        output.first = K * exp(-r * T) * StdNormalCDF::CDF(-d2) - S * StdNormalCDF::CDF(-d1);
        // Delta
        output.second = StdNormalCDF::CDF(d1) - 1;
    } else {
        cout << "Error! Option type must be one of 'P'/'p' or 'C'/'c'!" << endl;
        // if incorrect input
        output.first = -1;
        output.second = -2; // since delta is bounded by -1 and 1 inclusive
    };

    return output;
};

std::pair<double, double> Option_Price::Binomial_Pricer() {
    // initialize variables
    double K, S, r, T, vol;
    K = Option::get_K();
    S = Option::get_S();
    r = Option::get_r();
    T = Option::get_T();
    vol = Option::get_vol();

    // Initialize constants
    double u, d, q_u, q_d, dT, sqrt_T;
    int n_intervals;
    pair<double, double> output;
//    vector<double> bin_tree(n_intervals + 1); // to store binomial tree values

    // Return -1, -2 if incorrect input
    if (K < 0 || S < 0 || T < 0 || r < 0 || vol < 0){
        cout << "Error! All inputs must be non-negative!" << endl;
        // if incorrect input
        output.first = -1;
        output.second = -2; // since delta is bounded by -1 and 1 inclusive
        return output;
    }

    /******** Translating from QCF notes ***********/
    dT = 0.001; // make smaller for more accuracy
    sqrt_T = sqrt(dT);
    n_intervals = T/dT;
    u = exp(vol * sqrt_T);
    d = 1 / u;
    q_u = (exp(r * dT) - d) / (u - d);
    q_d = 1 - q_u;

    // Asset (Spot) Tree
    vector<vector<double>> S_t(n_intervals + 1, vector<double>(n_intervals + 1)); // to store binomial tree values
    for (int i = 0; i <= n_intervals; i++) {
        for (int j = 0; j <= n_intervals; j++) {
            S_t[i][j] = S * pow(u, j) * pow(d, i - j);
        };
    };

    // Derivative Tree
    // (i+1, j+1) denotes when underlying Spot went up
    vector<vector<double>> D_t(n_intervals + 1, vector<double>(n_intervals + 1)); // to store binomial tree values
    for (int x = 0; x <= n_intervals; x++) {
        if (flag == "C" or flag == "c") {
            D_t[n_intervals][x] = (S_t[n_intervals][x] > K) ? S_t[n_intervals][x] - K : 0;
        }
        else if (flag == "P" or flag == "p") {
            D_t[n_intervals][x] = (S_t[n_intervals][x] < K) ? K - S_t[n_intervals][x] : 0;
        }
    }

    // Populate tree backward as in the notes
    for (int i = n_intervals - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            D_t[i][j] =  (q_u * D_t[i + 1][j + 1] + q_d * D_t[i + 1][j]) * exp(-r * dT);
        }
    }


    if (flag == "C" or flag == "c") {
        if (T == 0) {
            output.first = (S > K) ? S - K : 0;
            output.second = 0.5;
            return output;
        } else {
            output.first = D_t[0][0];
            output.second = (D_t[1][1] - D_t[0][0]) / (S_t[1][1] - S_t[0][0]);
        }
    }
    else if (flag == "P" or flag == "p") {
            if(T==0){
                if (K - S > 0) { output.first = K - S; } else { output.first = 0; }
                output.second = -0.5;
                return output;
            } else {
                output.first = D_t[0][0];
                output.second = (D_t[1][1] - D_t[0][0]) / (S_t[1][1] - S_t[0][0]);
            }
    }
    else {
        cout << "Error! Option type must be one of 'P'/'p' or 'C'/'c'!" << endl;
        output.first = -1;
        output.second = -2; // since delta is bounded by -1 and 1 inclusive
    }

    /******* Using Wikipedia Pseudocode (not so accurate) ********/
//    // Compute common constants
//    dT = T / n_intervals;
//    sqrt_T = sqrt(dT);
//    u = exp(vol * sqrt_T);
//    d = 1 / u;
//    q_u = (exp(r * dT) - d) / (u - d);
//    q_d = 1 - q_u;
//
//    // Check Aribtrage Free Pricing
////    assert(d < exp(r * dT) < u);
//
//    // calculate option value and delta
//    if (flag == "C" or flag == "c") {
//
//        // handle T = 0 edge case
//        if(T==0){
//            if (S - K > 0) {output.first = S - K;} else {output.first = 0;}
//            output.second = 0.5;
//            return output;
//        };
//
//        // Initial Values at time T
//        for (int i = 0; i <= n_intervals; i++) {
//            bin_tree[i] = S * pow(u, 2 * i - n_intervals) - K;
//            if (bin_tree[i] < 0) { bin_tree[i] = 0; };
//        }
//
//        for (int j = n_intervals - 1; j >= 0; j--) {
//            for (int i = 0; i <= j; i++) {
//                // Binomial Value
//                bin_tree[i] = q_u * bin_tree[i + 1] + q_d * bin_tree[i];
//                // Exercise Value
//                double E = S * pow(u, 2 * i - j) - K;
//                if (bin_tree[i] < E) { bin_tree[i] = E; };
//            }
//        }
//        // Option Value
//        output.first = bin_tree[0];
//        // Delta
//        output.second = (bin_tree[1] - bin_tree[0]) / (S * u - S);
//
//        // limit bounds of Binomial Delta
//        if (output.second < -1) {output.second = -1;}
//        else if (output.second > 1) {output.second = 1;}
//    } else if (flag == "P" or flag == "p") {
//        // handle T = 0 edge case
//        if(T==0){
//            if (K - S > 0) {output.first = K - S;} else {output.first = 0;}
//            output.second = -0.5;
//            return output;
//        };
//
//        // Initial Values at time T
//        for (int i = 0; i <= n_intervals; i++) {
//            bin_tree[i] = K - S * pow(u, 2 * i - n_intervals);
//            if (bin_tree[i] < 0) { bin_tree[i] = 0; };
//        }
//
//        for (int j = n_intervals - 1; j >= 0; j--) {
//            for (int i = 0; i <= j; i++) {
//                // Binomial Value
//                bin_tree[i] = q_u * bin_tree[i + 1] + q_d * bin_tree[i];
//                // Exercise Value
//                double E = K - S * pow(u, 2 * i - j);
//                if (bin_tree[i] < E) { bin_tree[i] = E; };
//            }
//        }
//        // Option Value
//        output.first = bin_tree[0];
//        // Delta
//        output.second = (bin_tree[1] - bin_tree[0]) / (S - S * d);
//
//        // limit bounds of Binomial Delta
//        if (output.second < -1) {output.second = -1;}
//        else if (output.second > 1) {output.second = 1;}
//    } else {
//        // if incorrect input
//        cout << "Error! Option type must be one of 'P'/'p' or 'C'/'c'!" << endl;
//        output.first = -1;
//        output.second = -2; // since delta is bounded by -1 and 1 inclusive
//    };

    return output;
}
