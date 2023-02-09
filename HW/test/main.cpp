#include "bond.h"
#include "derivative.h"
#include <iostream>
#include <string>
using namespace std;

int main(void) {

//    Bond b1, b2("12/19/2035", 0.05, 0.07);
//
//    std::cout << b2.ToString() << endl;
//    std::cout << b1.ToString() << endl;
//
//    std::cout << "Example bond" << endl;
//    std::cout << b1.pv(3.85, 0.08, 0.075, 0.25) << endl;
//
//    std::cout << "Test Bond" << endl;
//    std::cout << b1.pv("7/15/2022", "12/17/2026", 0.06, 0.08, 0.5) << endl;
//

    std::cout << "Example derivative" << endl;
    Derivative d("8/3/2015", "1/1/2016", "12/31/2020", "../Bond_Ex3.csv", 0.5, 0.05);
    std::cout << "Expected Payoff" << endl;
    double payoff = d.get_payoff("1/1/2016", "12/31/2020", 0.5, 0.05);
    std::cout << payoff << endl;
    std::cout << "Implied Price" << endl;
    std::cout << d.pv_derivative("8/3/2015", "12/31/2020", payoff) << endl;

    double maturity = d.get_maturity("8/3/2015", "12/31/2020");
    double r = d.get_rate(maturity);
    double discount = exp(-r * maturity);
    cout << payoff * discount;

    return 0;
}