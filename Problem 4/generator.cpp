#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[])
{
    // Defaults
    int numPoints = 15;
    float xRange = 50.0f;
    float yRange = 50.0f;
    std::string filename = "input.txt";

    if (argc >= 4)
    {
        numPoints = atoi(argv[1]);
        xRange = static_cast<float>(atof(argv[2]));
        yRange = static_cast<float>(atof(argv[3]));
    }

    std::ofstream output(filename);

    if(!output.is_open())
    {
        std::cerr << "Output file couldn't open";
        return 1;
    }

    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<float> distX(0.0f, xRange);
    std::uniform_real_distribution<float> distY(0.0f, yRange);

    // Generate Points
    for (int i = 0; i < numPoints; ++i) output << distX(gen) << ' ' << distY(gen) << '\n';

    
    output.close();
    std::cout << "Generated file '" << filename << "' with " << numPoints << " points.\n";

    return 0;
}