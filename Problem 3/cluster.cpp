#include "cluster.hpp"

float calculateDistance(const Centroid& centroid, const Point& point)
{
    float deltaX = centroid.getX() - point.getX(), deltaY = centroid.getY() - point.getY();
    return std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
}



void recalculateCentroid(const std::vector<Point>& input, Centroid& centroid)
{
    float xTotal = 0, yTotal =0;
    for (const Point& p : input)
    {
        xTotal += p.getX();
        yTotal += p.getY();
    }
    centroid.setLoc({xTotal / input.size(), yTotal / input.size()});
}