#include "cluster.hpp"

float calculateDistance(const Location& centroid, const Location& point)
{
    float deltaX = centroid.getX() - point.getX(), deltaY = centroid.getY() - point.getY();
    return std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
}



void reCalculateCentroid(const std::vector<Location>& input, Location& centroid)
{
    float xTotal = 0, yTotal =0;
    for(Location l : input)
    {
        xTotal += l.getX();
        yTotal += l.getY();
    }
    centroid.setLoc({xTotal / input.size(), yTotal / input.size()});
}