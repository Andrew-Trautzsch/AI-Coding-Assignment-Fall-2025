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

    // read states
    input >> numStates;
    states.resize(numStates);
    for (int i = 0; i < numStates; i++)
        input >> states[i];

    // read emissiosn
    input >> numEmissions;
    emissions.resize(numEmissions);
    for (int i = 0; i < numEmissions; i++)
        input >> emissions[i];

    // read initial vector
    initial.resize(numStates);
    for (int i = 0; i < numStates; i++)
        input >> initial[i];

    // read transistion matrix
    transition.assign(numStates, std::vector<double>(numStates));
    for (int r = 0; r < numStates; r++)
        for (int c = 0; c < numStates; c++)
            input >> transition[r][c];

    // read emission matrix
    emissionMat.assign(numStates, std::vector<double>(numEmissions));
    for (int r = 0; r < numStates; r++)
        for (int c = 0; c < numEmissions; c++)
            input >> emissionMat[r][c];

    // read goal sequence
    input >> obsLength;
    goal.resize(obsLength);
    for (int i = 0; i < obsLength; i++)
        input >> goal[i];

    input.close();

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Error: could not open output.txt\n";
        return 1;
    }

    HMM model(states, emissions, initial, goal, transition, emissionMat);

    model.findPossibilities();

    out << "All Possible Paths and Their Probabilities\n\n";
    std::cout << "calculating odds...\n";
    double greatest = 0; std::vector<int> path;
    for(int i=0; i<model.posibilities_.size(); i++)
    {
        double tmp = model.calculateOdds(model.posibilities_[i]);
        out << "{";
        for(int c : model.posibilities_[i]) out << c << " ";
        out << "}  ->  " << tmp << "\n";
        if(greatest < tmp)
        {
            greatest = tmp;
            path = model.posibilities_[i];
        }
    }

    out << "\nMost optimal path is : {";
    for(int i : path) out << i << ", ";
    out << "} with odds of " << greatest;

    out.close();

    return 0;
}