# Lab 2

## Assignment Details

1. Implement a Black-Scholes Option Class with a member function calculating
implied volatility.
2. Load the SPY options prices from a csv file "spy_options.csv" and store data
into a Pandas dataframe. Implement a function which returns a dataframe containing
all options prices with strike prices falling in a given range. The dataframe shall
contain information on whether the option is a call or a put, the corresponding
strike price and the market price of the option.
3. Implement a function which generates a plot with x-axis corresponding to the
sorted strike prices and y-axis corresponding to the implied volatility calculated
by Black-Scholes model.

## Coding Details
- The `BSM.py` file hold the BSM class which is the Black-Scholes Option Class with a member function calculating
implied volatility.
- The `utils.py` file holds helper functions that are implemented in `main.py`. This includes cleaning the dataframe
as well as obtaining important features for the BSM pricer.
- The `main.py` runs the script. Note that the risk free rate was obtained from the 1-month treasury bill and the SPY
price was obtained from `pandas_datareader` package. If you do not have that installed run in your terminal:

```
pip install pandas_datareader
```
## Results
Observe the Volatility Smile below:

![Vol_Smile](Vol_Smile.png)