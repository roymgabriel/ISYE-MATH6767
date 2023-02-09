#ifndef BOND_H
#define BOND_H
#include <math.h>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

class Bond {

private:
    int par;
    std::string expiration;
    double period;
    double coupon;
    tm* convert_string(string);


public:
    Bond();
    Bond(const Bond&);
    Bond(string expiration, double period, double coupon);
    std::string ToString();
    double pv(double, double, double, double);
    double pv(string, string, double, double, double);
    double pv(string, double);
    ~Bond();
    double get_maturity(string, string);
    double get_price(double, double, double, double);
};

#endif