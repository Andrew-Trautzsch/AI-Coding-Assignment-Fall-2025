#include "cluster.hpp"

int main()
{
    // given list of points and centroids
    std::vector<Point> points = {
        // Cluster A (bottom-left)
        Point(0, 1.0f, 1.5f),
        Point(1, 2.0f, 2.2f),
        Point(2, 3.0f, 1.9f),
        // Cluster B (upper-middle)
        Point(3, 4.0f, 6.0f),
        Point(4, 5.0f, 5.8f),
        Point(5, 6.0f, 6.5f),
        // Cluster C (upper-right)
        Point(6, 7.0f, 8.5f),
        Point(7, 8.0f, 9.1f),
        Point(8, 9.0f, 9.3f),
        Point(9, 30.0f, 8.6f)
    };

    std::vector<Centroid> centroids = {
        Centroid(0, 2.0f, 2.0f, 0.0f),
        Centroid(1, 7.0f, 7.0f, 0.0f)
    };

    // used for comparison to check if loop can end
    std::vector<std::vector<float>> holder(centroids.size(), std::vector<float>(points.size()));

    while(true)
    {
        // table of distances for each iteration
        std::vector<std::vector<float>> distances(centroids.size(), std::vector<float>(points.size(), 0.0f));
        
        // map of centroid belongings
        std::unordered_map<int, std::vector<Point>> groups;

        // computes distance table
        for(int j=0; j<points.size(); j++) // point
        {
            int belongsTo = -1;
            float smallest = -1;
            for(int i=0; i<centroids.size(); i++) // centroid
            {
                // goes point by point rather than centroid to give points their centroids
                float dist = calculateDistance(centroids[i], points[j]);
                distances[i][j] = dist;

                if (i == 0 || dist < smallest) {
                    smallest = dist;
                    belongsTo = centroids[i].getId();
                }
            }
            points[j].assignCentroid(belongsTo);
            if(centroids[belongsTo].getRadius() > smallest) points[j].assignOutlier(true);
            else points[j].assignOutlier(false);
            groups[belongsTo].push_back(points[j]);
        }

        // check if changes are present
        if(holder == distances) {std::cout << "complete" << std::endl; return 1;}
        holder = distances;

        std::cout << "\nFinal centroid positions:\n";
        for (const auto& c : centroids) {
            c.printCen();
            std::cout << " -> ";
            c.printLoc();
            std::cout << '\n';
        }

        std::cout << "\nPoint assignments:\n";
        for (const auto& p : points) {
            p.printLoc();
            std::cout << " -> Centroid ";
            p.printCen();
            std::cout << '\n';
        }

        // recalculate centroids
        for(Centroid& l : centroids)
        {
            recalculateCentroid(groups[l.getId()],l);
        }

    }

    std::cout << "failed" << std::endl;
    return 0;
}