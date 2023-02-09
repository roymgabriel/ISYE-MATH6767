//
// Created by Roy Makkar Gabriel on 10/10/22.
//

#ifndef Option_h
#define Option_h

#include <string>
using namespace std;

class Option {
private:
    // define Strike(K), Spot(S), risk-free-rate(r), Time to Maturity(T), volatility(vol)
    double K, S, r, vol, OP;

    // define hedging period parameters
    string t_0, t_N, flag;

    // init method with default parameters
    void init(double Strike, double Spot, double OP, double rfr, string F, string t0, string tN);

public:
    // Default Constructor
    Option();

    // Constructor with parameters
    Option(double Strike, double Spot, double OP, double rfr, string F, string t0, string tN);

    // Destructor
    ~Option() = default;

    // get() method for each parameter
    double get_K() const, get_S() const, get_r() const, get_OP() const, get_T(string start_date, string end_date);
    string get_t_0() const, get_t_N() const, get_flag() const;

    // BSM Pricer
    double BSM_Pricer(double vol);
};


#endif //Option_h
