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
        for(int j=0; j<points.size(); j++)
        {
            int belongsTo = -1;
            bool isOutlier = false;
            for(int i=0; j<centroids.size(); i++)
            {
                // goes point by point rather than centroid to give points their centroids
                distances[i][j] = calculateDistance(points[j],centroids[i]);
                if(j==0) {
                    belongsTo = centroids[i].getId();
                }
                else 
                {
                    belongsTo = distances[i][j] > distances[i][j-1]? centroids[j-1].getId():centroids[j].getId();
                    if() // ADD OUTLIER STEP
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
        if(holder == distances) return 1;
        holder = distances;
    }

    return 0;
}