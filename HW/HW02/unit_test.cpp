//
// Created by Roy Makkar Gabriel on 9/17/22.
//

#include "bond.h"
#include "unit_test.h"
#include <iostream>
#include <string>

using namespace std;

bool UnitTestClass::Default_Bond() {
    // Declare Bond
    bond simple_bond;
    // Test Default Constructor and its initialization
    cout << "Testing Default Constructor..." << endl;
    cout << "Expected Output: Bond (, 0.000000, 0.000000)" << endl;
    cout << "Code Output: " << simple_bond.ToString() << endl;

    return simple_bond.ToString() == "Bond (, 0.000000, 0.000000)";
};

bool UnitTestClass::CC_Bond(const bond &) {
    // Declare Bond
    bond simple_bond;
    bond copy_bond(simple_bond);
    // Test Copy Constructor
    std::cout << "Testing Copy Constructor... " << endl;
    std::cout << "Expected Output: " << "Bond ({Expiration Date}, {Frequency}, {Coupon Rate})" << endl;
    std::cout << "Code Output: " << copy_bond.ToString() << endl;
    return simple_bond.ToString() == copy_bond.ToString();
};

void UnitTestClass::Defined_Bond(string ED, double f, double cr) {
    // Declare Bond
    bond defined_bond(ED, f, cr);
    // Testing Defined Bond Class
    std::cout << "Testing Constructor... " << endl;
    std::cout << "Expected Output: " << "Bond ({Expiration Date}, {Frequency}, {Coupon Rate})" << endl;
    std::cout << "Code Output: " << defined_bond.ToString() << endl;
};

void UnitTestClass::Bond_PV(double T, double DR, double CR, double f, double FV) {
    // Declare Bond
    bond b;
    // Testing PV Calculations
    std::cout << "Testing Bond PV Pricer... " << endl;
    std::cout << "Expected Output: Present Value of the Bond discounted with respect to the {DR}." <<  endl;
    cout << "Bond Price: " << b.Bond_Pricer(T, DR, CR, f, FV) << endl;
}

void UnitTestClass::weird_T(double T, double DR, double CR, double f, double FV) {
    // Declare Bond
    bond b;
    // Testing PV Calculations
    std::cout << "Testing Bond PV Pricer with incorrect inputs... " << endl;
    std::cout << "Expected Output: ERROR! Expiration Date cannot be < 0!" <<  endl;
    cout << "Bond Price: " << b.Bond_Pricer(T, DR, CR, f, FV) << endl;
}

void UnitTestClass::weird_FV(double T, double DR, double CR, double f, double FV) {
    // Declare Bond
    bond b;
    // Testing PV Calculations
    std::cout << "Testing Bond PV Pricer with incorrect inputs... " << endl;
    std::cout << "Expected Output: ERROR! Face Value cannot be < 0!" <<  endl;
    cout << "Bond Price: " << b.Bond_Pricer(T, DR, CR, f, FV) << endl;
}

void UnitTestClass::weird_Freq(double T, double DR, double CR, double f, double FV) {
    // Declare Bond
    bond b;
    // Testing PV Calculations
    std::cout << "Testing Bond PV Pricer with incorrect inputs... " << endl;
    std::cout << "Expected Output: ERROR! Frequency cannot be < 0!" <<  endl;
    cout << "Bond Price: " << b.Bond_Pricer(T, DR, CR, f, FV) << endl;
}
