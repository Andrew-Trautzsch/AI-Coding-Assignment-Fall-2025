#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_map>

class Location
{
public:
    Location(int id, float x, float y) :  id_(id), x_(x), y_(y) {}
    float getX() const {return x_;}
    float getY() const {return y_;}
protected:
    float x_, y_;
    int id_ = -1;
};

class Centroid;

class Point : public Location
{
public:
    Point(int id, float x, float y) : Location(id,x,y) {}

    // Mutators
    void assignCentroid(int input) {centroid_ = input;}
    void assignOutlier(bool input) {outlier_ = input;}

    // Accessors
    void printLoc() {std::cout << '(' << x_ << ',' << y_ << ')';}
    void printCen() {std::cout << centroid_;}
    void printOut() {std::cout << outlier_;}

private:
    int centroid_ = -1;
    bool outlier_ = 1;
};

class Centroid : public Location
{
public:
    Centroid(int id, float x, float y, float radius) : Location(id,x,y), radius_(radius) {}

    // Mutators
    void setLoc(const std::pair<float,float>& input) {x_ = input.first; y_ = input.second;}

    // Accessors
    void printLoc() {std::cout << '(' << x_ << ',' << y_ << ')';}
    void printCen() {std::cout << id_;}
    int getId() {return id_;}
    float getRadius() {return radius_;}

private:
    float radius_ = 0;
};

float calculateDistance(const Centroid&, const Point&);
void recalculateCentroid(const std::vector<Point>&, Centroid&);

#endif // CLUSTER_HPP