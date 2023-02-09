//
// Created by Roy Makkar Gabriel on 10/1/22.
//

#include "Option.h"
using namespace std;

// Define init
void Option::init(double Strike=100, double Spot=100, double rfr=0.1, double ttm=0.1, double volatility=0.2) {
    K = Strike;
    S = Spot;
    r = rfr;
    T = ttm;
    vol = volatility;
}


// call init method to initialize variables
Option::Option() {
    init();
}

// Constructor with parameters
Option::Option(double Strike, double Spot, double rfr, double ttm, double volatility) {
    init(Strike, Spot, rfr, ttm, volatility);
};

// Define get methods
double Option::get_K() const {return K;};
double Option::get_S() const {return S;};
double Option::get_r() const {return r;};
double Option::get_T() const {return T;};
double Option::get_vol() const {return vol;};

