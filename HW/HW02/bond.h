//
// Created by Roy Makkar Gabriel on 9/17/22.
//

#ifndef bond_h
#define bond_h
#include <iostream>

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
    double Bond_Pricer(double time_to_maturity, double interest_rate, double coupon_rate, double frequency,
                       double face_value) const;

    double Bond_Pricer_Dates(string start_date, string end_date, double interest_rate, double coupon_rate, double frequency,
                      double face_value);

    double DateDiff(string start_date, string end_date);


    /* Exercise 3 */
    double average(vector<double> v) const;

    static double find_rate(double);

    double special_BP(string start_date, string end_date, double CR, double freq,
                      double face_value = 100);

    double PV_special_BP(string purchase_date, string end_date, double sp_BP);

    double DaysToYear(int);

    };

#endif //bond_h
