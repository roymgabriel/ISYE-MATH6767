#include <iostream>
#include <vector>
#include <numeric>
#include "bond.h"
#include "unit_test.h"

using namespace std;

int main() {

    // Exercise 1:
    cout << "Running Exercise 1...\n\n" << endl;
    // Define Default Variables
    string Time = "01-01-2023"; /* Expires on January 1st, 2023*/
    double Freq = 0.5; /* Semi Annually */
    double Coup = 0.07; /* 7% */

    // Declare bond class
    bond b1(Time, Freq, Coup);

    // Print Default Bond to std::out
    cout << "Default Bond To String Function: " << endl;
    cout << b1.ToString() << endl;

    // Semi-annually compounded bond
    Time = "11-19-2035"; /* Expires on November 19th, 2035*/
    Freq = 0.5; /* Semi Annually */
    Coup = 0.07; /* 7% */

    // Declare a second bond class
    bond b2(Time, Freq, Coup);

    // Print Default Bond to std::out
    cout << "Define Bond Output: " << endl;
    cout << b2.ToString() << endl;

    /* Exercise 2 */
    cout << "Running Exercise 2...\n\n" << endl;

    // Define parameters
    double T = 3.85;
    double FV = 100;
    double CR = 0.075;
    double DR = 0.08;
    double f = 0.25;

    cout << "Bond Price with predefined parameters: " << endl;
    cout << "PLEASE NOTE: If you get no output or a negative PV, that means you have an invalid input!" << endl;
    cout << "Bond Price: " << b2.Bond_Pricer(T, DR, CR, f, FV) << endl;

    cout << "\nPlease Enter the time to maturity, discount rate, coupon rate, frequency, and face value of the coupon." << endl;
    cout << "Examples: " << endl;
    cout << "T = 4.3, DR = 0.08, CR = 0.075, f = 0.5, fv = 100" << endl;
    cout << "Note that you will have to enter each value on a new line and in the order asked." << endl;
    cin >> T >> DR >> CR >> f >> FV;
    cout << "Bond Price: " << b2.Bond_Pricer(T, DR, CR, f, FV) << endl;

    /* Exercise 3 */
    cout << "Running Exercise 3...\n\n" << endl;

    bond b3("01-01-2016",0.5, 0.05);
    double Bond_Payoff = b3.special_BP("01-01-2016", "12-31-2020", 0.05, 0.5, 100);
    cout << "Bond Payoff (2020): " << Bond_Payoff << endl;
    std::cout << "Present Value of Special Bond" << endl;
    std::cout << b3.PV_special_BP("08-03-2015", "12-31-2020", Bond_Payoff) << endl;

    cout << "End of Exercises...\n\n" << endl;

    /* UnitTests */UnitTestClass UTC;
    cout << "\nResults of Unit Tests: " << endl;
    cout << "Default Constructor: \n" << UTC.Default_Bond() <<endl;

    bond b_temp;
    cout << "Copy Constructor: \n" << UTC.CC_Bond(b_temp) <<endl;
    cout << "Please Enter Bond Details as follows: " << endl;
    cout << "Date (in the format of mm-dd-yyyy)" << endl;
    cout << "Frequency (0.5 denotes coupon with semi-annual payments)" << endl;
    cout << "Coupon Rate (0.05 denotes a 5% coupon rate)" << endl;
    cin >> Time >> f >> FV;
    cout << "Defined Constructor: \n"  <<endl;
    UTC.Defined_Bond(Time, f, FV);

    cout << "Please Enter Bond Details as you did earlier in the exercise: " << endl;
    cout << "Inputs (Time to Expiration, Discount Rate, Coupon Rate, frequency, face value)" << endl;
    cin >> T >> DR >> CR >> f >> FV;
    cout << "Bond PV: \n"  << endl;
    UTC.Bond_PV(T, DR, CR, f, FV);

    cout << "Please Enter an Invalid Time to Maturity: " << endl;
    cin >> T;
    cout << "Invalid Time To Maturity: \n" << endl;
    UTC.weird_T(T, DR, CR, f, FV);

    cout << "Please Enter an Invalid Face Value: " << endl;
    cin >> FV;
    cout << "Invalid Face Value: \n" << endl;
    UTC.weird_FV(T, DR, CR, f, FV);

    cout << "Please Enter an Invalid frequency: " << endl;
    cin >> f;
    cout << "Invalid Frequency: \n" << endl;
    UTC.weird_Freq(T, DR, CR, f, FV);

    return 0;
}
