#include <iostream>

/// Simple Point class used for keeping track of the heroes position ///
/// and calculating the moves that they have available ...           ///

class Point {
private:
    int x, y;
public:
    // Constructors
    Point() : x(0), y(0) {}

    Point(int in_x, int in_y) 
        : x(in_x), y(in_y) {}

    // Accessors
    int getX() const { return x; }
    int getY() const { return y; }

    // Overloads
    Point& operator=(const Point& rhs) {
        if (this != &rhs) {
            x = rhs.x;
            y = rhs.y;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& rhs) {
        os << '(' << rhs.x << ", " << rhs.y << ')';
        return os;
    }
};