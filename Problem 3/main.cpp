#include "cluster.hpp"

int main()
{
    std::vector<Location> points, centroids;

    std::vector<std::vector<float>> holder;

    while(true)
    {
        new std::vector<std::vector<float>> distances;
        for(int i=0; i<centroids.size(); i++)
        {
            float smallest = -1;
            for(int j=0; j<points.size(); j++)
            {
                distances[i][j] = calculateDistance(i,j);
                if(j==0) smallest = centroids[i].getId();
                else smallest = min(smallest,distances[i][j]);
            }
        }
        


        if(holder == distances) return 1;

        holder = distances;
        delete distances;
    }

    return 0;
}