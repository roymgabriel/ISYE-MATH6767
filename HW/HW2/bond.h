//
// Created by Roy Makkar Gabriel on 9/17/22.
//

#ifndef BOND_H
#define BOND_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class bond {
private:
    string expiration_date;
    double frequency;
    double coupon_rate;

public:
    /* Exercise 1 */
    // Default Constructor
    // string expiration_date = 0, double frequency = 0, double coupon_rate = 0
    bond();

    // Destructor
    ~bond() {};

    // Copy Constructor
    bond(const bond &);

    // Constructor
    bond(string expiration_date, double frequency, double coupon_rate);

    // To_String function
    string ToString() const;

    /* Exercise 2 */
    // Bond Pricer
    static double Bond_Pricer(double time_to_maturity, double interest_rate, double coupon_rate, double frequency,
                       double face_value) ;

    static double DateDiff(string start_date, string end_date);


    /* Exercise 3 */
    static double average(const vector<double> &v);

    static double find_rate(double);

    static double special_BP(string start_date, string end_date, double CR, double freq,
                      double face_value = 100);

    static double PV_special_BP(string purchase_date, string end_date, double sp_BP);

    static double DaysToYear(int);

};

#endif
