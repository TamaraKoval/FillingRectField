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

Coord Coord::operator+(double num) const {
    Coord temp;
    temp.x = x + num;
    temp.y = y + num;
    return temp;
}

Coord Coord::operator-(double num) const {
    Coord temp;
    temp.x = x - num;
    temp.y = y - num;
    return temp;
}

Coord Coord::operator*(double num) const {
    Coord temp;
    temp.x = x * num;
    temp.y = y * num;
    return temp;
}

std::ostream& operator<<(std::ostream& stream, Coord& coords) {
    stream << "(" << coords.getX() << "," << coords.getY() << ")";
    return stream;
}

double RectByCoords::getHeight() const {
    return maxPoint.getY() - minPoint.getY();
}

double RectByCoords::getWidth() const {
    return maxPoint.getX() - minPoint.getX();
}

Coord RectByCoords::getCenter() {
    double centerX = (minPoint.getX() + maxPoint.getX()) / 2;
    double centerY = (minPoint.getY() + maxPoint.getY()) / 2;
    return { centerX, centerY };
}

RectByCoords& RectByCoords::operator=(const RectByCoords& r) {
    this->minPoint = r.minPoint;
    this->maxPoint = r.maxPoint;
    return *this;
}

bool RectByCoords::isValid() const {
    return minPoint.getX() < maxPoint.getX() && minPoint.getY() < maxPoint.getY();
}

bool RectByCoords::contain(const Coord& coord) const {
    return coord.getX() <= maxPoint.getX() && coord.getX() >= minPoint.getX() && coord.getY() <= maxPoint.getY() && coord.getY() >= minPoint.getY();
}

bool DoubleCircle::isValid() const {
    return innerRad > 0 && outterRad > 0 && outterRad >= innerRad;
}