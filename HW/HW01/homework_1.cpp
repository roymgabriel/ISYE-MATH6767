#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;


double average(vector<double> v)
{
// code for calculating average of members of v
// and returning the average
    double s = 0;
    for (int i = 0; i <= v.size(); ++i) {
        s += v[i];
    }
    return v.empty() ? 0 : s/v.size();
}

double find_rate(vector<double> rate_vec, vector<string> date_vec, string date)
{
// code for finding the Baa rate for the
// given date (in yyyy-mm format)
// and returning the rate for that month
    for (int i = 0; i < date_vec.size(); ++i) {
        if (date == date_vec[i]){
            return rate_vec[i];
        }
    }
    return -1;
}

int main()
{
    // code for loading rate and date vectors from the file hw1_H.15_Baa_Data.csv
    // the headers should be handled properly. do not delete them manually

    // code for prompting user for a date and returning the rate
    // and the difference between the rate for that date and the
    // average rate
    //
    // This code should allow the user to continue to input dates
    // until the user inputs the EOF (End-of-file), namely control-d (in linux/mac) or control-z (in windows)
    // This should not crash if a bad date is entered.

    vector<double> rate;
    vector<string> date;

    ifstream infile("./hw1_H.15_Baa_Data.csv");
    if (!infile.is_open()) {
        cout << "File Open ERROR! Most probably a path problem!" << endl;
        return 1.0;
    }

    string line;
    string temp_date;
    string temp_rate;
    vector<string> dates;
    vector<double> rates;

    while(getline (infile, line)){
        if (isalpha(line[0])==0) {
            temp_date = line.substr(0, line.find(","));
            temp_rate = line.substr(line.find(",") + 1);
            temp_rate = temp_rate.substr(0, temp_rate.find("\r"));
            dates.push_back(temp_date);
            rates.push_back(stod(temp_rate));
        }
    }

    infile.close();

    string input_date;
    double rate_output;
    double rate_diff;

    cout << "Please enter a date: \n";

    while(getline(cin, input_date)) {
        rate_output = find_rate(rates, dates, input_date);
        if (rate_output == -1) {
            cout << "Date entered is invalid! \nPlease enter a valid Date (between 1919-01 and 2013-07 in the form YYYY-MM): \n" << endl;
        }
        else {
            rate_diff = rate_output - average(rates);
            cout << "Rate: " << rate_output << endl;
            cout << "Diff: " << rate_diff << endl;
        }
    }
   return 0.0; // program end
}

