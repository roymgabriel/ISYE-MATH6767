#include "derivative.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

Derivative::Derivative() : Bond() {
    purchase = "";
    start = "";
    end = "";
}

Derivative::Derivative(string purchase, string start, string end, string path, double frequency, double coupon_rate)
        : Bond(end, frequency, coupon_rate)
{
    purchase = purchase;
    start = start;
    end = end;
    data = Derivative::get_data(path);
}

Derivative::~Derivative() {}

vector<pair<double, double> > Derivative::get_data(string path) {

    ifstream infile(path);
    string line;
    pair<double, double> vals;
    vector<pair<double, double> > data;

    while (getline(infile, line))
    {
        if (isalpha(line[0]) == 0) {
            int delim = line.find(',');
            string ttm = line.substr(0, delim);
            string rate = line.substr(delim + 1);
            vals.first = stod(ttm);
            vals.second = stod(rate);
            data.push_back(vals);
        }
    }
    return data;
}

double Derivative::get_rate(double maturity) {

    double rate;
    for (int i = 0; i < data.size(); i++) {
        if (maturity >= data[i].first) {
            rate = data[i].second;
            break;
        }
    }
    return rate;
}

double Derivative::get_payoff(string start, string end, double frequency, double coupon_rate) {

    double time_difference = Bond::get_maturity(start, end);
    double partial = time_difference - floor(time_difference);
    int tot_periods = floor(time_difference);
    double avg_price = 0;
    double partial_maturity_price = Bond::pv(partial, Derivative::get_rate(partial), coupon_rate, frequency);

    for (int i = 1; i <= tot_periods; i++) {
        avg_price += Bond::pv(i, Derivative::get_rate(i), coupon_rate, frequency);
    }
    avg_price += partial_maturity_price;
    return avg_price / (tot_periods + 1);
}

double Derivative::pv_derivative(string purchase, string end, double payoff) {

    double maturity = Bond::get_maturity(purchase, end);
    double r = Derivative::get_rate(maturity);
    double discount = exp(-r * maturity);
    return payoff * discount;
}