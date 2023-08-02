#include "Geometry.h"
#include <iostream>

void Coord::SetCoord(int xx, int yy) {
    x = xx;
    y = yy;
}

Coord& Coord::operator=(Coord c) {
    this->x = c.x;
    this->y = c.y;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, Coord& coords) {
    stream << "(" << coords.getX() << "," << coords.getY() << ")";
    return stream;
}

bool Rect::isValid() {
    return minPoint.getX() < maxPoint.getX() && minPoint.getY() < maxPoint.getY();
}

bool Rect::contain(Coord coord) {
    return coord.getX() <= maxPoint.getX() && coord.getX() >= minPoint.getX() && 
        coord.getY() <= maxPoint.getY() && coord.getY() >= minPoint.getY();
}

bool DoubleCircle::isValid() {
    return innerRad > 0 && outterRad > 0 && outterRad >= innerRad;
}

bool DoubleCircle::operator<(DoubleCircle dc) {
    return outterRad < dc.outterRad;
}
