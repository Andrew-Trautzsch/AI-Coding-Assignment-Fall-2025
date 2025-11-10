#include "cluster.hpp"

float calculateDistance(const Location&, const Location&)
{

}



void recalculateCentroid(const std::vector<Location>& input, Location& centroid)
{
    float xTotal = 0, yTotal =0;
    for(Location l : input)
    {
        xTotal += l.getX();
        yTotal += l.getY();
    }
    centroid.setLoc({xTotal / input.size(), yTotal / input.size()});
}