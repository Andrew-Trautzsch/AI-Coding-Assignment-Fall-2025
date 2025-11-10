#include "cluster.hpp"

int main()
{
    // given list of points and centroids
    std::vector<Point> points;
    std::vector<Centroid> centroids;

    // used for comparison to check if loop can end
    std::vector<std::vector<float>> holder(centroids.size(), std::vector<float>(points.size()));

    while(true)
    {
        // table of distances for each iteration
        std::vector<std::vector<float>> distances;
        
        // map of centroid belongings
        std::unordered_map<int, std::vector<Point>> groups;

        // computes distance table
        for(int j=0; j<points.size(); j++) // point
        {
            int belongsTo = -1;
            float smallest = -1;
            bool isOutlier = false;
            for(int i=0; j<centroids.size(); i++) // centroid
            {
                // goes point by point rather than centroid to give points their centroids
                distances[i][j] = calculateDistance(centroids[i], points[j]);
                if(j==0) {
                    belongsTo = centroids[i].getId();
                    smallest = distances[i][j];
                }
                else 
                {
                    belongsTo = distances[i][j] > distances[i][j-1] ? centroids[j-1].getId():centroids[j].getId();
                    belongsTo = distances[i][j] > distances[i][j-1] ? distances[i][j-1]:distances[i][j];
                }
            }
            points[j].assignCentroid(belongsTo);
            groups[belongsTo].push_back(points[j]);
        }

        // recalculate centroids
        for(Centroid l : centroids)
        {
            recalculateCentroid(groups[l.getId()],l);
        }

        // check if changes are present
        if(holder == distances) {std::cout << "complete" << std::endl; return 1;}
        holder = distances;
    }

    std::cout << "failed" << std::endl;
    return 0;
}