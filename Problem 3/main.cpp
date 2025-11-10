#include "cluster.hpp"

int main()
{
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: could not open input.txt\n";
        return 1;
    }

    char type;
    int id;
    float x, y, radius;

    std::vector<Centroid> centroids;
    std::vector<Point> points;

    while (input >> type) {
        if (type == 'C') {
            input >> id >> x >> y >> radius;
            centroids.emplace_back(id, x, y, radius);
        } 
        else if (type == 'P') {
            input >> id >> x >> y;
            points.emplace_back(id, x, y);
        }
    }

    input.close();

    std::ofstream output("output.txt");
    
    if(!output.is_open())
    {
        std::cerr << "Output file couldn't open";
        return 1;
    }

    // used for comparison to check if loop can end
    std::vector<std::vector<float>> holder(centroids.size(), std::vector<float>(points.size()));
    int iteration = 1;

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
        if(holder == distances) {output << "\ncomplete"; output.close(); return 1;}
        holder = distances;

        output << "\nIteration " << iteration << " centroid positions:\n";
        for (const auto& c : centroids) {
            output << c.getId() << " -> (" << c.getX() << ", " << c.getY() << ")\n";
        }

        output << "\nPoint assignments:\n";
        for (const auto& p : points) {
            output << "(" << p.getX() << ", " << p.getY() << ")"<< " -> Centroid " << p.getCen() << ", is Outlier: " << (p.getOut()?"True":"False") << '\n';
        }

        // recalculate centroids
        for(Centroid& l : centroids)
        {
            recalculateCentroid(groups[l.getId()],l);
        }
        iteration++;
    }

    std::cout << "failed" << std::endl;
    return 0;
}