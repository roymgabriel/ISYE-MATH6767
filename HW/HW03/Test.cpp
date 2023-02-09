//
// Created by Roy Makkar Gabriel on 10/2/22.
//

#include "Test.h"
#include "Option_Price.h"
#include "Pricing_Method.h"
#include "Option.h"

bool Test::check_default_option() {
    // check default option
    double K, S, r, T, vol;
    Option op;
    K = op.get_K();
    S = op.get_S();
    r = op.get_r();
    T = op.get_T();
    vol = op.get_vol();
    return K == 100 and S == 100 and r == 0.1 and T == 0.1 and vol == 0.2;
};

bool Test::check_option(double K, double S, double r, double T, double vol) {
    // Check a manually constructed Option
    Option op(K, S, r, T, vol);
    double strike, spot, rfr, ttm, v;
    strike = op.get_K();
    spot = op.get_S();
    rfr = op.get_r();
    ttm = op.get_T();
    v = op.get_vol();
    return strike == K and spot == S and rfr == r and ttm == T and v == vol;
};

bool Test::check_incorrect_strike_BS(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.BSM_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_spot_BS(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.BSM_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_rate_BS(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.BSM_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_time_BS(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.BSM_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_vol_BS(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.BSM_Pricer();
    return output == test_output;
};
bool Test::check_incorrect_strike_BP(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.Binomial_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_spot_BP(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.Binomial_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_rate_BP(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.Binomial_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_time_BP(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.Binomial_Pricer();
    return output == test_output;
};

bool Test::check_incorrect_vol_BP(double Strike, double Spot, double rfr, double ttm, double volatility) {
    // check if BSM pricer returns -1, -2 on error input
    std::pair<double, double> output, test_output;
    output.first = -1;
    output.second = -2;

    Option_Price OPr("C", Strike, Spot, rfr, ttm, volatility);
    test_output = OPr.Binomial_Pricer();
    return output == test_output;
};