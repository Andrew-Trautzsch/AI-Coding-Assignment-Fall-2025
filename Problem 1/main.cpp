#include "hmm.hpp"

int main()
{
    // default info
    std::vector<int> states = {1, 2};  // Rainy, Sunny

    std::vector<char> emissions = {'W', 'S', 'C'}; 

    std::vector<double> initial = {0.6, 0.4};

    std::vector<std::vector<double>> transition = {
        {0.7, 0.3},   // From Rainy -> (Rainy, Sunny)
        {0.4, 0.6}    // From Sunny -> (Rainy, Sunny)
    };

    std::vector<std::vector<double>> emission = {
        {0.1, 0.4, 0.5}, // Rainy -> Walk, Shop, Clean
        {0.6, 0.3, 0.1}  // Sunny -> Walk, Shop, Clean
    };

    std::vector<char> goal = {'W','S','C'};
    //

    HMM model(states, emissions, initial, goal, transition, emission);

    for(int i=0; i<goal.size(); i++)
    {
        model.calculateStep(i);
    }
    
    model.backTrack();
    return 0;
}