//
// Created by Roy Makkar Gabriel on 10/1/22.
//

// Header Guards
#ifndef StdNormalCDF_h
#define StdNormalCDF_h

#include <iostream>
using namespace std;

// Using CamelCase for all names
class StdNormalCDF{
private:
    static const double a1, a2, a3, a4, a5, p;

public:
    static double CDF(double x) ;
};

#endif // StdNormalCDF_h