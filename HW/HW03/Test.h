//
// Created by Roy Makkar Gabriel on 10/2/22.
//

#ifndef Test_h
#define Test_h


class Test {
public:
    bool check_default_option();
    static bool check_option(double, double, double, double, double);
    static bool check_incorrect_strike_BS(double, double, double, double, double);
    static bool check_incorrect_spot_BS(double, double, double, double, double);
    static bool check_incorrect_time_BS(double, double, double, double, double);
    static bool check_incorrect_rate_BS(double, double, double, double, double);
    static bool check_incorrect_vol_BS(double, double, double, double, double);
    static bool check_incorrect_strike_BP(double, double, double, double, double);
    static bool check_incorrect_spot_BP(double, double, double, double, double);
    static bool check_incorrect_time_BP(double, double, double, double, double);
    static bool check_incorrect_rate_BP(double, double, double, double, double);
    static bool check_incorrect_vol_BP(double, double, double, double, double);
};


#endif //Test_h
