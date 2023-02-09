//
// Created by Roy Makkar Gabriel on 10/1/22.
//
#include "Option.h"
#include "Pricing_Method.h"
#include <string>

#ifndef Option_Price_h
#define Option_Price_h

using namespace std;

class Option_Price: public Option, public Pricing_Method {

public:
    // Constructor
    Option_Price();
    // Destructor
    ~Option_Price();
    // Constructor with defined input
    Option_Price(string F, double K, double S, double r, double T, double vol);

    // BSM Pricer
    pair<double, double> BSM_Pricer() override;
    // Binomial Pricer
    pair<double, double> Binomial_Pricer() override;

    // Declare Number of Intervals for Binomial Tree
    int n_intervals;
    // Declare flag member variable
    string flag;

};


#endif //Option_Price_h