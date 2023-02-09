#include "bond.h"
#include <iostream>
#include <string>


Bond::Bond() {
    expiration = "";
    period = 0.0;
    coupon = 0.0;
    par = 100;
}

Bond::Bond(const Bond& b) {
    expiration = b.expiration;
    period = b.period;
    coupon = b.coupon;
    par = 100;
}

Bond::Bond(string end, double frequency, double cr_rate) {
    expiration = end;
    period = frequency;
    coupon = cr_rate;
    par = 100;
}

string Bond::ToString() {
    ostringstream freq, c;
    freq << fixed << setprecision(1) << Bond::period;
    c << fixed << setprecision(2) << Bond::coupon;
    return "Bond(" + Bond::expiration + ", " + freq.str() + ", " + c.str() + ")";
}

tm* Bond::convert_string(string date_string) {


    int m, y, d;
    int first = date_string.find('/');
    int second = date_string.rfind('/');
    m = stoi(date_string.substr(0, first));
    d = stoi(date_string.substr(first + 1, second));
    y = stoi(date_string.substr(second + 1));
    tm* date = new tm;
    date->tm_year = y - 1900; // tm struct counts years starting from 1900
    date->tm_mon = m - 1; // tm struct counts months [0;11]
    date->tm_mday = d;
    return date;
}

double Bond::get_maturity(string start, string end) {
    tm* start_date, * end_date;
    start_date = Bond::convert_string(start);
    end_date = Bond::convert_string(end);
    double years = end_date->tm_year - start_date->tm_year;
    double months = (end_date->tm_mon - start_date->tm_mon) / 12;
    double days = (end_date->tm_mday - start_date->tm_mday) / 365;
    double maturity = years + months + days;
    delete start_date;
    delete end_date;
    return maturity;
}

double Bond::get_price(double maturity, double discount_rate, double coupon_rate, double frequency) {

    double discount, value = 0;
    double partial = (maturity - floor(maturity));
    int periods = int(floor(maturity)) / frequency;
    double partial_cf = 0;
    double cf = par * coupon_rate * frequency;

    if (partial / frequency < 1) {
        partial_cf = cf * (1- (partial / frequency));
        discount = exp(-discount_rate * partial);
        value += partial_cf * discount;

        for (int i = 1; i <= (periods); i++) {
            discount = exp(-discount_rate * frequency * (i + partial));
            value += cf * discount;
        }
    } else {
        double p_diff = partial - frequency;
        partial_cf = cf * (1 - (p_diff / frequency));
        discount = exp(-discount_rate * p_diff);
        value += partial_cf * discount;

        for (int i = 1; i <= (periods + 1); i++) {
            discount = exp(-discount_rate * frequency * (i + p_diff));
            value += cf * discount;
        }
    }
    value += par * exp(-discount_rate * maturity);

    return value;
}

double Bond::pv(double maturity, double discount_rate, double coupon_rate, double frequency) {

    return Bond::get_price(maturity, discount_rate, coupon_rate, frequency);
}

double Bond::pv(string start, string end, double discount_rate, double coupon_rate, double frequency) {

    double maturity = Bond::get_maturity(start, end);
    return Bond::get_price(maturity, discount_rate, coupon_rate, frequency);
}

double Bond::pv(string start, double discount_rate) {

    double maturity = Bond::get_maturity(start, expiration);
    return Bond::get_price(maturity, discount_rate, coupon, period);
}

Bond::~Bond() {}




