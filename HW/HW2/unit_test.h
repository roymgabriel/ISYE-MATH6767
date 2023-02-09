//
// Created by Roy Makkar Gabriel on 9/17/22.
//

#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include "bond.h"

using namespace std;

class UnitTestClass{
public:
    bool Default_Bond();
    bool CC_Bond(const bond &);
    void Defined_Bond(string expiration_date, double frequency, double coupon_rate);
    void Bond_PV(double T, double DR, double CR, double f, double FV);
    void weird_T(double T, double DR, double CR, double f, double FV);
    void weird_FV(double T, double DR, double CR, double f, double FV);
    void weird_Freq(double T, double DR, double CR, double f, double FV);
};

#endif
