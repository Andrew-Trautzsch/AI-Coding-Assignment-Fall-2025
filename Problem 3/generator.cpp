#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[])
{
    // Defaults
    int numClusters = 2;
    int numPoints = 15;
    float xRange = 50.0f;
    float yRange = 50.0f;
    float radius = 5.0f;
    std::string filename = "input.txt";

    if (argc >= 6)
    {
        numClusters = atoi(argv[1]);
        numPoints = atoi(argv[2]);
        xRange = static_cast<float>(atof(argv[3]));
        yRange = static_cast<float>(atof(argv[4]));
        radius = static_cast<float>(atof(argv[5]));
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
    std::uniform_real_distribution<float> distR(0.0f, radius);

    // Generate Centroids
    for (int i = 0; i < numClusters; ++i) output << "C " << i << ' ' << distX(gen) << ' ' << distY(gen) << ' ' << distR << '\n';

    // Generate Points
    for (int i = 0; i < numPoints; ++i) output << "P " << i << ' ' << distX(gen) << ' ' << distY(gen) << '\n';

    
    output.close();
    std::cout << "Generated file '" << filename << "' with " << numClusters << " centroids and " << numPoints << " points.\n";

    return 0;
}