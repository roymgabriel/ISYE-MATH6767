# Assignment 2

Design a Bond Class and price the bond based on user input. Further, price a special bond based on given constraints.

# The Data
The data, in the form of a csv file, consists of corresponding interest rates based on bond time to expiration values. 

# The Assignment
The program will go through each exercise as prompted in the PDF assignment. In the first exercise, the program will output Bond details using a function call `ToString`.
In the second exercise the program will price a bond based on default values but will also prompt the user to enter bond details and it will return the present value of the bond.
In the third exercise, the program will price the bond based on the average of the 2016-2020 payouts discounted back to 2015 using a non-constant interest rate. The discounting factors are chosen based on the csv file attached.

# Getting Started
The easiest way to run the code is to use JetBrains' CLion. Navigate to the `main.cpp` and click run. This works best for mac and windows.
Please note that I have a mac, and I run a function called `strptime` that might cause some errors for windows users.

If you want to compile from your command line, change into the directory where you downloaded the program. Then run:
```c++
g++ *.cpp
./a.out
```
You could also compile the C++ code and name the program you want to run. For example:
```c++
g++ -o <name-your-program-here> *.cpp
./newprogram
```

When running the program follow the instructions. When printing the details of the bond, make sure to enter the dates based on the format asked.
When asked to define the bond parameters, make sure to input each value on a new line and in the order mentioned.

See attached photos for details.

![](./sc1.jpg)
![](./sc2.jpg)
![](./sc3.jpg)
