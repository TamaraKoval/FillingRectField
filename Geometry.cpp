#include "Geometry.h"

Coord& Coord::operator=(const Coord& c) {
    this->x = c.x;
    this->y = c.y;
    return *this;
}

Coord Coord::operator+(const Coord& c) const {
    Coord temp;
    temp.x = x + c.x;
    temp.y = y + c.y;
    return temp;
}

Coord Coord::operator-(const Coord& c) const {
    Coord temp;
    temp.x = x - c.x;
    temp.y = y - c.y;
    return temp;
}

std::ostream& operator<<(std::ostream& stream, Coord& coords) {
    stream << "(" << coords.getX() << "," << coords.getY() << ")";
    return stream;
}

Coord Rect::getCenter() {
    double centerX = (minPoint.getX() + maxPoint.getX()) / 2;
    double centerY = (minPoint.getY() + maxPoint.getY()) / 2;
    return { centerX, centerY };
}

Rect& Rect::operator=(const Rect& r) {
    this->minPoint = r.minPoint;
    this->maxPoint = r.maxPoint;
    return *this;
}

bool Rect::isValid() const {
    return minPoint.getX() < maxPoint.getX() && minPoint.getY() < maxPoint.getY();
}

bool Rect::contain(const Coord& coord) const {
    return coord.getX() <= maxPoint.getX() && coord.getX() >= minPoint.getX() && coord.getY() <= maxPoint.getY() && coord.getY() >= minPoint.getY();
}

bool DoubleCircle::isValid() const {
    return innerRad > 0 && outterRad > 0 && outterRad >= innerRad;
}