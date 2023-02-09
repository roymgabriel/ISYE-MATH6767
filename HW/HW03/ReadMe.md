# Assignment 3

Design an Options Pricing class that takes the Option's parameters as inputs and outputs the Black Scholes Merton Option
Value and its corresponding delta as well as the Binomial price value and its corresponding delta.

# The Assignment
There are three essential classes and one unit test class. The `Option` class declares and defines the parameters of an 
Option (strike, spot, etc.). The `Option_Price` class declares and defines the two pricer functions: Black Scholes Merton
and Binomial Pricing method. The third class is the `Pricing_Method` class, which is an abstract class. The `Option_Price`
class derives from `Option` class and `Pricing_Method` class.

# Getting Started
The easiest way to run the code is to use JetBrains' CLion. Navigate to the `main.cpp` and click run. This works best for mac and windows.

If you wish to compile from your command line, change into the directory where you downloaded the program. Then run:
```c++
g++ *.cpp
./a.out
```
You could also compile the C++ code and name the program you want to run. For example:
```c++
g++ -o <name-your-program-here> *.cpp
./newprogram
```

When running the program follow the instructions printed to console. Do not enter negative values for any of the option
parameters unless if it was for testing purposes. The returned values for any incorrect inputs are
`-1` for the Option Value and `-2` for the Option Delta (since delta is bounded between -1 and 1).

