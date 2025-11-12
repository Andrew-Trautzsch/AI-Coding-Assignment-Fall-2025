#ifndef HMM_HPP
#define HMM_HPP

#include <iostream>
#include <fstream>
#include <vector>

struct HMM 
{
    HMM(const std::vector<int>&, const std::vector<char>&, const std::vector<double>&, const std::vector<char>&);

    void calculateStep(int);
    int getEmissionIndex(char);
    void backTrack();

    std::vector<int> states_; // 1,2,3,...,n
    std::vector<char> emissions_; // A,B,C,...,m
    std::vector<double> initial_;
    std::vector<char> goal_;

    std::vector<std::vector<double>> traTable_; // transistion matrix
    std::vector<std::vector<double>> emiTable_; // emissions matrix
    std::vector<std::vector<double>> proTable_; // saves probablity for each step, used for backtracking solution
};

#endif // HMM_HPP