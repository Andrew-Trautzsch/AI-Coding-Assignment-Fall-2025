# AI Coding Assignment Fall 2025 - CS 44201/54201

Programming HW assignment, consists of 4 problems.

All programs come with a generator file that creates parameterized data to test with

To run programs, install GCC with MinGW: https://code.visualstudio.com/docs/cpp/config-mingw

all programs can be compiled and ran with:

- for data generation:
 - g++ generator.cpp -o generator.exe
 - .\generator.exe
- for running the program:
 - g++ main.cpp ... (other .cpp files) -o main.exe
 - .\main.exe

## 1. Hidden Markov Model Program

Description:

'Write a program for hidden Markov model that calculates most probable path based upon the
given observation. The program should take as input a sequence of probable observations. The
graph size should be parameterized, and the weights of the graphs should be generated using a
random number generator or read from a file.'

## 2. Feed Forward Neural Network

Description:

'Write a multi hidden layered (with number of hidden layers as parameter) neural network
program with m input variables and n output variables. The size m, n and number of perceptrons
in hidden layers are parameterized. Initially use random number function to give weights to the
edges. Generate your test data (meaningfully) using a simple algorithm, and then test it out on
neural network. There must be at least 100 test data for training.'

## 3. K-means Clustering Algorithm

Description:

'Write a K-means clustering program, and test it out on some practical problem using data
generated using random number generator or data read from a file.'

## 4. Linear Regression Analysis Algorithm

Description:

'Write a linear regression analysis program that finds out the fitting line plot for the given data,
and predicts the value of a dependent variable given the value of an independent variable. '

