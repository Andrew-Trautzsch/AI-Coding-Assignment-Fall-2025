#include "hmm.hpp"

int HMM::getGoalIndex(char input)
{
    for(int i=0; i<emissions_.size(); i++)
    {
        if (input == emissions_[i]) return i;
    }
    return -1;
}

void HMM::generatePaths(const std::vector<std::vector<int>>& validOptions)
{
    std::vector<int> current;
    generatePathsHelper(validOptions, current, 0);
}

void HMM::generatePathsHelper(const std::vector<std::vector<int>>& validOptions, std::vector<int>& current, int depth)
{
    if (current.size() == goal_.size())
    {
        posibilities_.push_back(current);
        return;
    }
    for(int i : validOptions[depth])
    {
        current.push_back(i);
        generatePathsHelper(validOptions, current, depth+1);
        current.pop_back();
    }
}

void HMM::findPossibilities()
{
    std::cout << "Calculating possibilities...\n";
    std::vector<std::vector<int>> validOptions(goal_.size());

    for(int i=0; i<states_.size(); i++)
    {
        if(emiTable_[i][getGoalIndex(goal_[0])] != 0) validOptions[0].push_back(i);
    }

    for(int i=1; i<goal_.size(); i++)
    {
        for(int j=0; j<states_.size(); j++)
        {
            if(emiTable_[j][getGoalIndex(goal_[i])] != 0) validOptions[i].push_back(i);
        }
    }

    std::cout << "Generating paths...\n";
    generatePaths(validOptions);

    std::cout << "Trimming paths...\n";
    for(auto it = posibilities_.begin(); it != posibilities_.end(); )
    {
        const std::vector<int>& path = *it;
        bool tmp = true; // is a valid path
        for(int i=0; i<path.size()-1; i++)
        {
            if(traTable_[path[i]][path[i+1]] == 0) tmp = false;
        }
        if(tmp) it++;
        else it = posibilities_.erase(it);
    }

}

double HMM::calculateOdds(const std::vector<int>& input)
{
    double output = (emiTable_[input[0]][getGoalIndex(goal_[0])]) * (initial_[input[0]]);

    for(int i=1; i<input.size(); i++)
    {
        output = output * (emiTable_[input[i]][getGoalIndex(goal_[i])]) * (traTable_[input[i-1]][input[i]]);
    }

    return output;
}


