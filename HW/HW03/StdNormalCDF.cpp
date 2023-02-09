//
// Created by Roy Makkar Gabriel on 10/1/22.
//
#include "StdNormalCDF.h"
#include <cmath>
using namespace std;

const double StdNormalCDF:: a1 = 0.319381530;
const double StdNormalCDF:: a2 = -0.356563782;
const double StdNormalCDF:: a3 = 1.781477937;
const double StdNormalCDF:: a4 = -1.821255978;
const double StdNormalCDF:: a5 = 1.330274429;
const double StdNormalCDF:: p = 0.2316419;

double StdNormalCDF::CDF(double x) {
    // to prevent overflow
    if (x > 6) { return 1.0; }
    if (x < -6) { return 0.0; }

    double z = 1/(1 + fabs(x)*p);
    double R = z*(z*(z*(z*(z*a5 + a4) + a3) + a2) + a1);

    if (x >= 0) {
        // return N(x)
        return 1 - ( 1/(sqrt(2*M_PI)) ) * exp(-pow(x, 2)/2) * R;
    }
    else {
        // return 1 - N(-x)
        return 1 - (1 - ( 1/(sqrt(2*M_PI)) ) * exp(-pow(-x, 2)/2) * R);
    }
}
