#ifndef DERIVATIVE_H
#define DERIVATIVE_H
#include <vector>
#include <iostream>
#include "bond.h"
using namespace std;

class Derivative: public Bond {

private:
    std::string purchase;
    std::string start;
    std::string end;
    vector<pair<double, double> > data;
    vector<pair<double, double> > get_data(string);


public:
    Derivative();
    Derivative(string, string, string, string, double, double);
    double get_payoff(string, string, double, double);
    double pv_derivative(string, string, double);
    ~Derivative();
    double get_rate(double);
};

#endif