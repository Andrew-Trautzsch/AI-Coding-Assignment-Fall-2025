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

    // std::cout << "\nIteration " << 0 << " centroid positions:\n";
    // for (const auto& c : centroids) {
    //     std::cout << c.getId() << " -> (" << c.getX() << ", " << c.getY() << ")\n";
    // }

    // std::cout << "\nPoint assignments:\n";
    // for (const auto& p : points) {
    //     std::cout << "(" << p.getX() << ", " << p.getY() << ")"<< " -> Centroid " << p.getCen() << ", is Outlier: " << (p.getOut()?"True":"False") << '\n';
    // }

    input.close();

    // std::vector<Point> points = {
    //     // Cluster A (bottom-left)
    //     Point(0, 1.0f, 1.5f),
    //     Point(1, 1.8f, 2.2f),
    //     Point(2, 2.4f, 1.9f),
    //     // Cluster B (upper-middle)
    //     Point(3, 5.5f, 6.0f),
    //     Point(4, 6.2f, 5.8f),
    //     Point(5, 5.7f, 6.5f),
    //     // Cluster C (upper-right)
    //     Point(6, 9.0f, 8.5f),
    //     Point(7, 8.2f, 9.1f),
    //     Point(8, 9.5f, 9.3f),
    //     Point(9, 8.8f, 8.6f)
    // };

    // std::vector<Centroid> centroids = {
    //     Centroid(0, 2.0f, 2.0f, 0.0f),
    //     Centroid(1, 7.0f, 7.0f, 0.0f)
    // };

    std::ofstream output("output.txt");
    
    if(!output.is_open())
    {
        std::cerr << "Output file couldn't open\n";
        return 1;
    }

    // used for comparison to check if loop can end
    std::vector<std::vector<float>> holder(centroids.size(), std::vector<float>(points.size()));
    int iteration = 1;

    // std::cout << "before while\n";
    while(true)
    {
        // table of distances for each iteration
        std::vector<std::vector<float>> distances(centroids.size(), std::vector<float>(points.size(), 0.0f));
        
        // map of centroid belongings
        std::unordered_map<int, std::vector<Point>> groups;

        // std::cout << "before for j\n";
        // computes distance table
        for(int j=0; j<points.size(); j++) // point
        {
            int belongsTo = -1;
            float smallest = -1;
            // std::cout << "before for i\n";
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
            // std::cout << "after for i\n";
            points[j].assignCentroid(belongsTo);
            if(centroids[belongsTo].getRadius() > smallest) points[j].assignOutlier(true);
            else points[j].assignOutlier(false);
            groups[belongsTo].push_back(points[j]);
        }
        // std::cout << "after for j\n";

        // check if changes are present
        if(holder == distances) {output << "\ncomplete"; std::cout << "complete\n"; output.close(); return 1;}
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
    // std::cout << "after while\n";

    std::cout << "failed" << std::endl;
    return 0;
}