#include "hmm.hpp"

HMM::HMM(const std::vector<int>& states, const std::vector<char>& emissions, const std::vector<double>& initial, const std::vector<char>& goal)
{
    std::cout << "\ninitializing...\n";
    // initialization
    states_ = states; emissions_ = emissions; initial_ = initial; goal_ = goal;

    // table creation
    for(int i=0; i<states_.size(); i++)
    {
        // transition (states_ * states_)
        for(int j; j<states_.size(); j++) {traTable_[i][j] = (states_[i] * states_[j]); std::cout << (states_[i] * states_[j]) << ' ';}
        std::cout << '\n';
        // emission (states_ * emissions_)
        for(int j; j<emissions_.size(); j++) {emiTable_[i][j] = (states_[i] * emissions[j]); std::cout << (states_[i] * emissions_[j]) << ' ';}
        std::cout << '\n';
    }
    
}

int HMM::getEmissionIndex(char input)
{
    for (int i=0; i<emissions_.size(); i++)
    {
        if(emissions_[i] == input) return i;
    }
    return -1;
}

void HMM::calculateStep(int stepNum)
{
    std::cout << "\nCurrent step: " << stepNum << '\n';
    // initialzie 'from' vector, check if needs initial_ vector
    std::vector<double> from;
    if(stepNum == 0) from = initial_;
    else from = proTable_[stepNum-1];

    int currentEmission = getEmissionIndex(goal_[stepNum]);

    // stores values of 'from' (inital/previous step) * 'to' (all states) * goal_[stepNum]
    std::vector<std::vector<double>> holder(states_.size(), std::vector<double>(from.size()));
    // 'to'
    for(int i=0; i<states_.size(); i++)
    {
        double greatest = 0;
        // 'from'
        for(int j=0; j<from.size(); j++)
        {
            double num = traTable_[i][j] * from[j] * emiTable_[i][currentEmission];
            holder[i][j] = num;
            std::cout << num << ' ';
            // take greatest odd to store in probablity table
            greatest = num>greatest?num:greatest;
        }
        std::cout << '\n';
        proTable_[stepNum][i] = greatest;
    }
}

void HMM::backTrack()
{
    std::cout << "\nbacktracking... \n";
    std::vector<int> path(goal_.size());
    for(int i=proTable_.size(); i>0; i--)
    {
        double greatest = 0;
        int holder = 0;
        for(int j=0; j<proTable_[i].size(); j++)
        {
            if (greatest > proTable_[i][j]) holder = j;
            else greatest = proTable_[i][j];
        }
        path[i-1] = states_[holder];
    }
    std::cout << "\nOptimal path is ";
    for(int i : path)
    {
        std::cout << i << ', ';
    }
    std::cout << '\n';
}