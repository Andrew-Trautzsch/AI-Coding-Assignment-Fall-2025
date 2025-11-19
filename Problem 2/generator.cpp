#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[])
{
    // Defaults
    int m = 3; // input size
    int n = 2; // output size
    int maxHiddenLayers = 3;
    int maxLayerSize = 5;
    std::string filename = "input.txt";

    if (argc >= 5) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
        maxHiddenLayers = atoi(argv[3]);
        maxLayerSize = atoi(argv[4]);
    }
    if (argc == 6) {
        filename = argv[5];
    }

    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::mt19937 gen(static_cast<unsigned>(time(nullptr)));
    std::uniform_real_distribution<double> distWeight(-1.0, 1.0);
    std::uniform_real_distribution<double> distVal(0.0, 1.0);
    std::uniform_int_distribution<int> distLayer(1, maxLayerSize);
    std::uniform_int_distribution<int> distCount(1, maxHiddenLayers);

    // generate input and output sizes
    out << m << " " << n << "\n";

    // generate input vector
    for (int i = 0; i < m; i++)
        out << distVal(gen) << " ";
    out << "\n";

    // generate desired output vector
    for (int i = 0; i < n; i++)
        out << distVal(gen) << " ";
    out << "\n";

    // generate num of hidden layers
    int numHiddenLayers = distCount(gen);
    out << numHiddenLayers << "\n";

    // generate layer sizes
    std::vector<int> layerSizes;
    for (int i = 0; i < numHiddenLayers; i++)
        layerSizes.push_back(distLayer(gen));

    // write layer sizes
    for (int s : layerSizes)
        out << s << " ";
    out << "\n";

    // generate layer weights and biases
    int prevSize = m;  // first layer takes input

    for (int idx = 0; idx < numHiddenLayers; idx++)
    {
        int currSize = layerSizes[idx];

        // write rows, cols
        out << currSize << " " << prevSize << "\n";

        // weights
        for (int r = 0; r < currSize; r++) {
            for (int c = 0; c < prevSize; c++) {
                out << distWeight(gen) << " ";
            }
            out << "\n";
        }

        // biases
        for (int r = 0; r < currSize; r++)
            out << distWeight(gen) << " ";
        out << "\n";

        prevSize = currSize;
    }

    // generate output layer
    out << n << " " << prevSize << "\n";

    // weights for output layer
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < prevSize; c++) {
            out << distWeight(gen) << " ";
        }
        out << "\n";
    }

    // biases for output layer
    for (int r = 0; r < n; r++)
        out << distWeight(gen) << " ";
    out << "\n";

    std::cout << "Generated ANN test file: " << filename << "\n";
    return 0;
}
