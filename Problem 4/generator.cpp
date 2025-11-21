#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[])
{
    // Defaults
    int numPoints = 15;
    int xRange = 50;
    int yRange = 50;
    std::string filename = "input.txt";

    if (argc >= 4)
    {
        numPoints = atoi(argv[1]);
        xRange = static_cast<int>(atof(argv[2]));
        yRange = static_cast<int>(atof(argv[3]));
    }

    std::ofstream output(filename);

    if(!output.is_open())
    {
        std::cerr << "Output file couldn't open";
        return 1;
    }

    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> distX(0, xRange);
    std::uniform_int_distribution<int> distY(0, yRange);

    // Generate Points
    for (int i = 0; i < numPoints; ++i) output << distX(gen) << ' ' << distY(gen) << '\n';

    
    output.close();
    std::cout << "Generated file '" << filename << "' with " << numPoints << " points.\n";

    return 0;
}