//
// Created by Roy Makkar Gabriel on 10/1/22.
//

#ifndef Option_h
#define Option_h

using namespace std;

class Option {
private:
    // define Strike(K), Spot(S), risk-free-rate(r), Time to Maturity(T), volatility(vol)
    double K, S, r, T, vol;
    // init method with default parameters
    void init(double Strike, double Spot, double rfr, double ttm, double volatility);
public:
    // Default Constructor
    Option();
    // Constructor with parameters
    Option(double Strike, double Spot, double rfr, double ttm, double volatility);
    // Destructor
    ~Option() = default;
    // get() method for each parameter
    double get_K() const, get_S() const, get_r() const, get_T() const, get_vol() const;
};


#endif //Option_h
