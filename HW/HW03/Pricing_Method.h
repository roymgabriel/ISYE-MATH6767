//
// Created by Roy Makkar Gabriel on 10/1/22.
//

#ifndef Pricing_Method_h
#define Pricing_Method_h
#include <iostream>

using namespace std;

class Pricing_Method {
public:
    // Pure Virtual Function - Black Scholes Options Pricer
    virtual pair<double, double> BSM_Pricer()=0;
    // Pure Virtual Function - Binomial Options Pricer
    virtual pair<double, double> Binomial_Pricer()=0;

    /** NOTE: Pricing_Method is an abstract class because there is more at least one pure virtual function declared **/
    /** NOTE: we have to override all pure virtual functions in the derived class **/
    /** NOTE: we do NOT define constructor destructor in abstract classes **/
};


#endif //Pricing_Method_h
