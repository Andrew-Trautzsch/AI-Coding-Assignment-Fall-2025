#ifndef CLUSTER.HPP
#define CLUSTER.HPP

#include <iostream>
#include <vector>

class Location
{
public:
    Location(float x, float y, int num = -1) : x_(x), y_(y), centroid_(num) {}
protected:
    float x_, y_;
    int centroid_ = -1;
};

class Centroid;

class Point : public Location
{
public:
    Point(float x, float y) : Location(x,y) {}

    float calculateDistance(const Centroid& input);

    // Mutators
    void assignCentroid(int input) {centroid_ = input;}
    void assignOutlier(bool input) {outlier_ = input;}

    // Accessors
    void printLoc() {std::cout << '(' << x_ << ',' << y_ << ')';}
    void printCen() {std::cout << centroid_;}
    void printOut() {std::cout << outlier_;}

private:
    bool outlier_ = 1;
    std::vector<Centroid> distance_;
};

class Centroid : public Location
{
public:
    Centroid(float x, float y, int num, float radius) : Location(x,y,num), radius_(radius) {}

    // Mutators
    void setLoc(float x, float y) {x_ = x; y_ = y;}

    // Accessors
    void printLoc() {std::cout << '(' << x_ << ',' << y_ << ')';}
    void printCen() {std::cout << centroid_;}

private:
    float radius_=0;
};


#endif // CLUSTER.HPP