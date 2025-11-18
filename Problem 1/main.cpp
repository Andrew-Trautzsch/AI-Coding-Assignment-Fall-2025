#include "hmm.hpp"

int main()
{
    // default info
    // std::vector<int> states = {1, 2};  // Rainy, Sunny

    // std::vector<char> emissions = {'W', 'S', 'C'}; 

    // std::vector<double> initial = {0.6, 0.4};

    // std::vector<std::vector<double>> transition = {
    //     {0.7, 0.3},   // From Rainy -> (Rainy, Sunny)
    //     {0.4, 0.6}    // From Sunny -> (Rainy, Sunny)
    // };

    // std::vector<std::vector<double>> emissionMat = {
    //     {0.1, 0.4, 0.5}, // Rainy -> Walk, Shop, Clean
    //     {0.6, 0.3, 0.1}  // Sunny -> Walk, Shop, Clean
    // };

    // std::vector<char> goal = {'W','S','C'};
    //

    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::vector<int> states;
    std::vector<char> emissions;
    std::vector<double> initial;
    std::vector<std::vector<double>> transition;
    std::vector<std::vector<double>> emissionMat;
    std::vector<char> goal;


    int numStates, numEmissions, obsLength;

    // -----------------------
    // Read states
    // -----------------------
    input >> numStates;
    states.resize(numStates);
    for (int i = 0; i < numStates; i++)
        input >> states[i];

    // -----------------------
    // Read emissions
    // -----------------------
    input >> numEmissions;
    emissions.resize(numEmissions);
    for (int i = 0; i < numEmissions; i++)
        input >> emissions[i];

    // -----------------------
    // Read initial probabilities
    // -----------------------
    initial.resize(numStates);
    for (int i = 0; i < numStates; i++)
        input >> initial[i];

    // -----------------------
    // Read transition matrix
    // -----------------------
    transition.assign(numStates, std::vector<double>(numStates));
    for (int r = 0; r < numStates; r++)
        for (int c = 0; c < numStates; c++)
            input >> transition[r][c];

    // -----------------------
    // Read emission matrix
    // -----------------------
    emissionMat.assign(numStates, std::vector<double>(numEmissions));
    for (int r = 0; r < numStates; r++)
        for (int c = 0; c < numEmissions; c++)
            input >> emissionMat[r][c];

    // -----------------------
    // Read observation sequence
    // -----------------------
    input >> obsLength;
    goal.resize(obsLength);
    for (int i = 0; i < obsLength; i++)
        input >> goal[i];


    HMM model(states, emissions, initial, goal, transition, emissionMat);

    model.findPossibilities();

    std::cout << "calculating odds...\n";
    double greatest = 0; std::vector<int> path;
    for(int i=0; i<model.posibilities_.size(); i++)
    {
        double tmp = model.calculateOdds(model.posibilities_[i]);
        if(greatest < tmp)
        {
            greatest = tmp;
            path = model.posibilities_[i];
        }
    }

    std::cout << "\nMost optimal path is : {";
    for(int i : path)
    {
        std::cout << i << ", ";
    }
    std::cout << "} with odds of " << greatest << "\n\n";

    return 0;
}