//
// Created by Roy Makkar Gabriel on 10/12/22.
//

#ifndef DeltaHedger_h
#define DeltaHedger_h

#include <string>
#include <vector>

using namespace std;

class DeltaHedger {
private:
    double S, K, T, r, mu, vol, N;
    string flag;

    // init method with default parameters
    void init() {
        S = 100,
        K = 105,
        T = 0.4,
        mu = 0.05,
        vol = 0.24,
        r = 0.025,
        N = 100,
        flag = "C";
    };

public:
    // Default Constructor
    DeltaHedger();

    // Constructor with parameters
    DeltaHedger(double Spot, double Strike, double ttm, double mean, double volatility, double rf,
                double n_simulations, string F);

    // Destructor
    ~DeltaHedger() = default;

    // Black-Scholes-Merton Pricer Function
    static double BSM_Pricer(double Spot, double Strike, double ttm, double volatility, double rf, const string& F);

    // Simulate a Sample Stock Path Function
    vector<double> SimulateStockSeries() const;

    // Simulate a Sample Option Path Function
    vector<double> SimulateOptionSeries(vector<double> stock_path);

    // Calculate Hedging Error
    vector<double> HedgingError(vector<double> stock_path, vector<double> option_path);

    // A function to start the simulation
    void SimulateSeries(int n_sim);


};

#endif //DeltaHedger_h
