//
// Created by Roy Makkar Gabriel on 10/12/22.
//

#include "DeltaHedger.h"
#include "StdNormalCDF.h"
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <utility>

using namespace std;

// Default Constructor
DeltaHedger::DeltaHedger() {init();}

// Default Constructor with parameters
DeltaHedger::DeltaHedger(double Spot, double Strike, double ttm, double mean, double sigma, double rf,
                         double n_simulations, string F) {
    S = Spot;
    K = Strike;
    T = ttm;
    mu = mean;
    vol = sigma;
    r = rf;
    N = n_simulations;
    flag = std::move(F);
    SimulateSeries(1000);
}

// Define Black Scholes Pricer
double DeltaHedger::BSM_Pricer(double Spot, double Strike, double ttm, double volatility, double rf, const string& F) {
    // initialize variables
    double output, d1, d2, sqrt_T;

    // Return -1, -2 if incorrect input
    if (Strike < 0 || Spot < 0 || ttm < 0 || rf < 0 || volatility < 0) {
        cout << "Error! All inputs must be non-negative!" << endl;
        // if incorrect input
        output = -1;
        return output;
    }

    // calculate common constants
    sqrt_T = sqrt(ttm);
    d1 = (log(Spot / Strike) + (rf + 0.5 * pow(volatility, 2)) * ttm) / (volatility * sqrt_T);
    d2 = d1 - (volatility * sqrt_T);

    // calculate option value and delta
    if (F == "C" or F == "c") {
        // handle T = 0 edge case
        if (ttm == 0) {
            output = (Spot > Strike) ? Spot - Strike : 0;
            return output;
        };

        // Option Value
        output = Spot * StdNormalCDF::CDF(d1) - Strike * exp(-rf * ttm) * StdNormalCDF::CDF(d2);

    } else if (F == "P" or F == "p") {
        // handle T = 0 edge case
        if (ttm == 0) {
            output = (Spot < Strike) ? Strike - Spot : 0;
            return output;
        };
        // Option Value
        output = Strike * exp(-rf * ttm) * StdNormalCDF::CDF(-d2) - Spot * StdNormalCDF::CDF(-d1);
    } else {
        cout << "Error! Option type must be one of 'P'/'p' or 'C'/'c'!" << endl;
        // if incorrect input
        output = -1;
    };

    return output;
};

// Simulate Stock Price
std::vector<double> DeltaHedger::SimulateStockSeries() const {

    // Generate Standard Normal random numbers (NOTE: We could have used Monte Carlo Attached library as well)
    std::vector<double> stock_vec(N + 1);
    std::random_device rand;
    std::mt19937 gen(rand());
    std::normal_distribution<float> StdNorm(0, 1);

    double dt = T / N;
    for (double i = 0; i <= N; i++) {
        if (i == 0) {
            stock_vec[i] = S;
        }
        else {
            double Z = StdNorm(gen);
            stock_vec[i] = stock_vec[i - 1] * (1 + mu * dt + vol * dt * Z);
        }
    }
    return stock_vec;
}

// Simulate Option Price
std::vector<double> DeltaHedger::SimulateOptionSeries(std::vector<double> stock_vec) {

    // Define variable types
    std::vector<double> option_vec(N + 1);

    // Generate BSM Price paths for option
    for (int i = 0; i <= N; i++) {
        option_vec[i] = BSM_Pricer(stock_vec[i], K, T, vol, r, flag);
    }
    return option_vec;
}

// Simulate Hedging Error
std::vector<double> DeltaHedger::HedgingError(std::vector<double> stock_vec, std::vector<double> option_vec) {
    // Initialize variables
    double temp_T, sqrt_T, d1, Nd1;
    std::vector<double> delta_vec(N + 1), B_vec(N + 1), HE_vec(N + 1);

    for (int i = 0; i <= N; i++) {
        temp_T = T - i * (T / N);
        sqrt_T = sqrt(temp_T);
        d1 = (log(stock_vec[i] / K) + (r + 0.5 * pow(vol, 2)) * temp_T) / (vol * sqrt_T);
        Nd1 = StdNormalCDF::CDF(d1);
        if (flag == "C" || flag == "C") {
            delta_vec[i] = Nd1;
        }
        else if (flag == "P" || flag == "p") {
            delta_vec[i] = Nd1 - 1;
        }
    }

    // Apply the Cumulative Hedging Error Formula till t_i
    // First Calculate B_i
    for (int i = 0; i <= N; i++) {
        if (i == 0) {
            B_vec[i] = option_vec[i] - delta_vec[i] * stock_vec[i];
        }
        else {
            B_vec[i] = (delta_vec[i - 1] - delta_vec[i]) * stock_vec[i] + B_vec[i - 1] * exp(r * (T / N));
        }
    }

    // Second Calculate HE
    for (int i = 0; i <= N; i++) {
        if (i == 0) {
            HE_vec[i] = 0;
        }
        else {
            HE_vec[i] = delta_vec[i - 1] * stock_vec[i] + B_vec[i - 1] * exp(r * (T / N)) - option_vec[i];
        }
    }
    return HE_vec;
}

// Simulate the paths and write results to csv file
void DeltaHedger::SimulateSeries(int n_sim) {
    // Define Variable types
    std::vector<std::vector<double>>  stock_vec(n_sim), option_vec(n_sim);
    std::vector<double>  HE_series(n_sim);

    // Simulate Stock and Option Path then store Hedging Error
    for (int i = 0; i < n_sim; i++) {
        stock_vec[i] = SimulateStockSeries();
        option_vec[i] = SimulateOptionSeries(stock_vec[i]);
        HE_series[i] = HedgingError(stock_vec[i], option_vec[i])[N];
    }

    // Output to files in directory
    ofstream f_stock, f_option, f_HE;

    // Store Stock Paths
    f_stock.open("../stock_simulation.csv");
    for (int i = 0; i < n_sim; i++) {
        for (int j = 0; j <= N; j++) {
            // Make it csv file
            f_stock << stock_vec[i][j] << ",";
        }
        f_stock << endl;
    }
    f_stock.close();

    // Store Option Paths
    f_option.open("../option_simulation.csv");
    for (int i = 0; i < n_sim; i++) {
        for (int j = 0; j <= N; j++) {
            // Make it csv file
            f_option << option_vec[i][j] << ",";
        }
        f_option << endl;
    }
    f_option.close();

    // Store Hedging Error Paths
    f_HE.open("../HE_simulation.csv");
    for (int i = 0; i < n_sim; i++) {
        // Make it csv file
        f_HE << HE_series[i] << endl;
    }
    f_HE.close();
}