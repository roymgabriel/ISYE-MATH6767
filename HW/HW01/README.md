# Assignment 1

Understand the implementation of C++ in the context of reading in csv files, interacting with user input, and calculating certain statistics.

# The Data
The data consists of time series data of Moody's yield on seasoned corporate bonds across all industries (BAA). There corresponds at each date a BAA rate.

# The Assignment
The program will ask the user to input a date, and the user would type any date (in the form of `YYYY-MM`) between `1919-01` and `2013-07`. In the event the user entered an incorrect date, the program will ask the user to try again.
Once a valid date has been entered, the program will output the BAA rate as well as the difference between the rate on that date and the average rate across all dates.

# Getting Started
Change into the directory where you downloaded the program. Then run:
```c++
g++ homework_1.cpp
./a.out
```
You could also compile the C++ code and name the program you want to run. For example:
```
g++ -o <name-your-program-here> homework_1.cpp
./newprogram
```
