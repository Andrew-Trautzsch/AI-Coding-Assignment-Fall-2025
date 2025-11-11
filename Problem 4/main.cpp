#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    // input of points
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    std::vector<std::pair<float,float>> points;
    //  = {
    //     {1,1},
    //     {1,2},
    //     {4,3},
    //     {8,5},
    //     {3,7},
    //     {2,4},
    //     {5,5},
    //     {10,4},
    //     {3,6},
    //     {7,7}
    // };

    float x, y;
    while (input >> x >> y)
    {
        points.push_back({x,y});
        // std::cout << x << ' ' << y << std::endl;
    }
    input.close();

    // Calculate X and Y means
    float xMean = 0, yMean = 0;
    for(std::pair<float,float> i : points) 
    {
        xMean += i.first;
        yMean += i.second;
    }
    xMean = (xMean/points.size()); yMean = (yMean/points.size());

    // Calculate X variance and XY covariance
    float varX = 0, coVarXY = 0;
    for(std::pair<float,float> i : points)
    {
        varX += ((i.first - xMean)*(i.first - xMean));
        coVarXY += ((i.first - xMean)*(i.second - yMean));
    }
    varX = (varX/(points.size()-1)); coVarXY = (coVarXY/(points.size()-1));

    // slope and intercept
    float slope = coVarXY / varX;
    float intercept = yMean - (slope*xMean);

    // y = mx + b
    std::cout << "y = m*x + b\n" << "y = " << slope << " * x + " << intercept << std::endl;

    while(true)
    {
        float input;
        std::cout << "Give a independent varible (x) to predict: ";
        std::cin >> input;
        std::pair<float,float> prediction = {input, (slope * input + intercept)};
        std::cout << "Predicted point is: (" << prediction.first << ',' << prediction.second << ")\n";
    }

    return 0;
}
