#include "Geometry.h"
#include <iostream>

Coord& Coord::operator=(Coord c) {
    this->x = c.x;
    this->y = c.y;
    return *this;
}

Coord Coord::operator+(Coord c) {
    Coord temp;
    temp.x = x + c.x;
    temp.y = y + c.y;
    return temp;
}

Coord Coord::operator-(Coord c) {
    Coord temp;
    temp.x = x - c.x;
    temp.y = y - c.y;
    return temp;
}

std::ostream& operator<<(std::ostream &stream, Coord &coords) {
    stream << "(" << coords.getX() << "," << coords.getY() << ")";
    return stream;
}

Coord Rect::getCenter() {
    int centerX = (minPoint.getX() + maxPoint.getX()) / 2;
    int centerY = (minPoint.getY() + maxPoint.getY()) / 2;
    return Coord(centerX, centerY);
}

Rect& Rect::operator=(Rect r) {
    this->minPoint = r.minPoint;
    this->maxPoint = r.maxPoint;
    return *this;
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
