//
// Created by Roy Makkar Gabriel on 10/12/22.
//

#ifndef DeltaHedgerWithInputData
#define DeltaHedgerWithInputData

#include <iostream>
#include <string>
#include <vector>
#include "Option.h"

using namespace std;

class DeltaHedgerWithInput {
private:
    // Declare Strike, start date, end date, and expiration date
    double K;
    string start_date, end_date, expiration_date;

public:
    // Default Constructor
    DeltaHedgerWithInput();

    // Default Constructor with parameters
    DeltaHedgerWithInput(string t_0, string t_N, string exp_date, double Strike);

    // Destructor
    ~DeltaHedgerWithInput()=default;

    // Vector of data type Option from the Option class
    vector<Option> option_array;
    // Declaring necessary vectors for columns in csv file
    vector<double> ivol_vec, delta_vec, PNL_vec, PNL_H_vec;

    // Function to read each of the csv files and combine them into option vector
    vector<Option> read_option();

    // Function to write to csv file
    void to_csv();

    // get() methods for each parameter
//    double get_match(vector<string> date_vector, vector<double> fin_data_array, string matching_val);
    vector<double> get_IV();
    vector<double> get_Delta();
    vector<double> get_HE();
    vector<double> get_PNL();
};

#endif //DeltaHedgerWithInputData
