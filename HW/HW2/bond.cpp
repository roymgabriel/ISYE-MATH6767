//
// Created by Roy Makkar Gabriel on 9/17/22.
//
#include <cmath>
#include <limits>
#include <utility>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include "bond.h"

using namespace std;

// Default Constructor Initializing the variables
bond::bond() {
    expiration_date = "";
    frequency = 0;
    coupon_rate = 0;
};

// Constructor
bond::bond(string end_date, double Freq, double Coup) {
    expiration_date = std::move(end_date);
    frequency = Freq;
    coupon_rate = Coup;
};

// Copy Constructor
bond::bond(const bond & b) {
    expiration_date = b.expiration_date;
    frequency = b.frequency;
    coupon_rate = b.coupon_rate;
};

// ToString function
string bond::ToString() const {
    return "Bond (" + bond::expiration_date + ", " + to_string(bond::frequency) + ", " + to_string(bond::coupon_rate) + ")";
};

/* Bond calculations to get maturity between dates */
// Count Leap Year
int CountLeapYears(int m, int d, int y){
    int temp_year = y;
    if (m <= 2){temp_year--;}
    return ( (temp_year / 4) - (temp_year / 100) + (temp_year / 400) );
}

// Valid Date Checker
bool isValidDate(string date){
    struct tm tm{};
    if (strptime(date.c_str(), "%m-%d-%Y", &tm)) {return true;}
    else if (date.size() == 10) {return true;}
    else {return false;}
};


// Time to maturity between two string dates
double bond::DateDiff(string start_date, string end_date){
    if (isValidDate(start_date) && (isValidDate(end_date))) {
        const int Month_Days[12] = { 31, 59, 90, 120, 151, 181, 212, 243,
                                     273, 304, 334, 365 };

        int month_start = stoi(start_date.substr(0, start_date.find('-')));
        int month_end = stoi(end_date.substr(0, end_date.find('-')));

        int day_start = stoi(start_date.substr(start_date.find('-') + 1, start_date.rfind('-')));
        int day_end = stoi(end_date.substr(end_date.find('-') + 1, end_date.rfind('-')));

        int year_start = stoi(start_date.substr(start_date.rfind('-') + 1));
        int year_end = stoi(end_date.substr(end_date.rfind('-') + 1));

        long int count_start_date = (year_start * 365);
        count_start_date += Month_Days[month_start-1] + day_start + CountLeapYears(month_start, day_start, year_start);

        long int count_end_date = (year_end * 365);
        count_end_date += Month_Days[month_end-1] + day_end + CountLeapYears(month_end, day_end, year_end);

        return abs(count_end_date - count_start_date);
    }
    else {
        cout << "Incorrect Date Input >> please input date in the format of mm-dd-yyyy." << endl;
        return -1;
    }
};


// Bond Pricer
double bond::Bond_Pricer(double time_to_maturity, double interest_rate, double coupon_rate, double frequency, double face_value = 100) {
    // TODO: check that there is no overload or div0 error
    // NOTE: OLD CLOSED FORM SOLUTION assuming constant interest rate -> CHANGING TO exponential for dynamic interest rates
//    double coupon = face_value * coupon_rate / frequency;
//    double PV_first_half = coupon * (1 - pow(1 + interest_rate/frequency, -time_to_maturity*frequency)) / (interest_rate/frequency);
//    double PV_second_half = face_value * pow(1 + interest_rate/frequency, -time_to_maturity*frequency);
//    return PV_first_half + PV_second_half;

    // Make sure inputs are good
    if (time_to_maturity < 0){cout << "ERROR! Expiration Date cannot be < 0!" << endl; return -1;}
    if (face_value < 0){cout << "ERROR! Face Value cannot be < 0!" << endl; return -1;}
    if (frequency < 0){cout << "ERROR! Frequency cannot be < 0!"; return -1;}

    double DF;
    double BondPrice = 0;
    double PartialCF;
    double partial_maturity = (time_to_maturity - floor(time_to_maturity));
    double partial_diff = partial_maturity - frequency;
    int adjusted_frequency = int(floor(time_to_maturity)) / frequency;
    double CF = face_value * coupon_rate * frequency;

    if (partial_maturity / frequency < 1){
        PartialCF = CF * (1 - partial_maturity / frequency);
        DF = exp(-interest_rate * partial_maturity);
        BondPrice += PartialCF * DF;

        for (int i = 1; i <= (adjusted_frequency); i++) {
            DF = exp(-interest_rate * frequency * (i + partial_maturity));
            BondPrice += CF * DF;
        }
    }
    else {
        PartialCF = CF * (1 - (partial_diff / frequency));
        DF = exp(-interest_rate * partial_diff);
        BondPrice += PartialCF * DF;

        for (int i = 1; i <= (adjusted_frequency+1); i++) {
            DF = exp(-interest_rate * frequency * (i + partial_diff));
            BondPrice += CF * DF;
        }
    }
    BondPrice += face_value * exp(-interest_rate * time_to_maturity);
    return BondPrice;
}

double bond::average(const vector<double> &v)
{
// code for calculating average of members of v
// and returning the average
    double s = 0;
    for (int i = 0; i <= v.size(); ++i) {
        s += v[i];
    }
    return v.empty() ? 0 : s/v.size();
}


double bond::find_rate(double T)
// code for finding the interest rate for the
// given bond time till maturity
// and returning the rate for that month

{
    ifstream infile("../Bond_Ex3.csv");
    if (!infile.is_open()) {
        cout << "File Open ERROR! Most probably a path problem!" << endl;
        return 1.0;
    }

    string line;
    string temp_T;
    string temp_rate;
    vector<double> ttm_vec;
    vector<double> rate_vec;
    vector<double> bond_prices;
    double temp_r;

    while(getline (infile, line)){
        if (isalpha(line[0])==0) {
            temp_T = line.substr(0, line.find(','));
            temp_rate = line.substr(line.find(',') + 1);
            temp_rate = temp_rate.substr(0, temp_rate.find('\r'));
            ttm_vec.push_back(stod(temp_T));
            rate_vec.push_back(stod(temp_rate));
        }
    }

    infile.close();

    double diff;
    double rv;
    double min_diff = numeric_limits<float>::max();
    for (int i = 0; i < ttm_vec.size(); ++i) {

        if (T == ttm_vec[i]){
            return rate_vec[i];
        }
        else{
            diff = abs(T - ttm_vec[i]);
            if (diff < min_diff) {
                min_diff = diff;
                rv = rate_vec[i];
            }
        }
    }

    return rv;
}

double bond::special_BP(string start_date, string end_date, double CR, double freq, double face_value) {
    // Code for calculating the special bond in Exercise 3

    int diff = DaysToYear(DateDiff(std::move(start_date), std::move(end_date))) - 1;
    cout << "Date Diff: " << diff << endl;
    double partial_maturity = diff - floor(diff);
    int all_adj_freq = floor(diff);
    vector <double> BP;
    double r_partial = bond::find_rate(partial_maturity);
    double partial_BP = bond::Bond_Pricer(partial_maturity, r_partial, CR, freq, face_value);

    for (int i = 1; i <= all_adj_freq ; i++) {
        double r = bond::find_rate(i);
        cout << 2021-i << " rate: " << r << endl;
        BP.push_back(Bond_Pricer(i, r, CR, freq, face_value));
    }

    BP.push_back(partial_BP);
    return average(BP);
}

double bond::DaysToYear(int days){
    // Convert Days to years including leap years
    int num_leaps = int( (days/4) / 365);
    int years = int(days / 365);
    int remaining_days = days % 365;
    return (years - (num_leaps / 365) + (remaining_days/ 365));

}
double bond::PV_special_BP(string purchase_date, string end_date, double sp_BP){
    // Discount the special bond back to 2015
    double ttm = DateDiff(std::move(purchase_date), std::move(end_date));
    double new_ttm = DaysToYear(ttm);
    double r = bond::find_rate(new_ttm);
    double DF = exp(-r * new_ttm);
    return sp_BP * DF;
}
