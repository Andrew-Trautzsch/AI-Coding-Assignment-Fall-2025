#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <numeric>

double randProb(std::mt19937& gen)
{
    std::uniform_real_distribution<double> dist(0.01, 1.0);
    return dist(gen);
}

// makes sure nums always adds up to 1
void normalize(std::vector<double>& row)
{
    double sum = std::accumulate(row.begin(), row.end(), 0.0);
    for (double& x : row) x /= sum;
}

int main(int argc, char* argv[])
{
    // Defaults
    int numStates = 2;
    int numEmissions = 3;
    int seqLength = 3;
    std::string filename = "input.txt";

    if (argc >= 4)
    {
        numStates = atoi(argv[1]);
        numEmissions = atoi(argv[2]);
        seqLength = atoi(argv[3]);
    }
    if (argc >= 5)
    {
        filename = argv[4];
    }

    std::ofstream output(filename);
    if (!output.is_open())
    {
        std::cerr << "Failed to open output file.\n";
        return 1;
    }

    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));

    // generate num of states
    output << numStates << "\n";
    for (int i = 0; i < numStates; i++) output << i << " ";
    output << "\n\n";

    // generate num of emissions
    output << numEmissions << "\n";
    for (int i = 0; i < numEmissions; i++)
    {
        char symbol = 'A' + i;
        output << symbol << " ";
    }
    output << "\n\n";

    // generate inital vector based on num of states
    {
        std::vector<double> row(numStates);
        for (double& x : row) x = randProb(gen);
        normalize(row);

        for (double x : row) output << x << " ";
        output << "\n\n";
    }

    // generates transistion table (states * states)
    for (int s = 0; s < numStates; s++)
    {
        // create random values and normalizes so values always add up to 1
        std::vector<double> row(numStates);
        for (double& x : row) x = randProb(gen);
        normalize(row);

        for (double x : row) output << x << " ";
        output << "\n";
    }
    output << "\n";

    // generates emissions table (states * emissions)
    for (int s = 0; s < numStates; s++)
    {
        // create random values and normalizes so values always add up to 1
        std::vector<double> row(numEmissions);
        for (double& x : row) x = randProb(gen);
        normalize(row);

        for (double x : row) output << x << " ";
        output << "\n";
    }
    output << "\n";

    // generates goal sequence based on length and emissions
    output << seqLength << "\n";
    std::uniform_int_distribution<int> eDist(0, numEmissions - 1);
    for (int i = 0; i < seqLength; i++)
    {
        char symbol = 'A' + eDist(gen);
        output << symbol << " ";
    }
    output << "\n";

    output.close();

    std::cout << "Generated HMM file: " << filename << "\n";
    std::cout << "States: " << numStates << ", Emissions: " << numEmissions << ", Obs-Length: " << seqLength << "\n";

    return 0;
}
