#pragma once
#include <ostream>

class Coord {
    double x, y;
public:
    Coord() : x(0), y(0) {}
    Coord(double xx, double yy) : x(xx), y(yy) {}
    void SetCoord(double xx, double yy) { x = xx; y = yy; }
    void SetX(double xx) { x = xx; }
    void SetY(double yy) { y = yy; }
    [[nodiscard]] double getX() const { return x; }
    [[nodiscard]] double getY() const { return y; }
    Coord& operator=(const Coord& c);
    Coord operator+(const Coord& c) const;
    Coord operator-(const Coord& c) const;
    Coord operator+(double num) const;
    Coord operator-(double num) const;
    Coord operator*(double num) const;
    friend std::ostream& operator<<(std::ostream& stream, Coord& coords);
};

class Validator {
public:
    [[nodiscard]] virtual bool isValid() const = 0;
};

class RectByCoords : public Validator {
    Coord minPoint, maxPoint;
public:
    RectByCoords() = default;
    RectByCoords(Coord min, Coord max) : minPoint(min), maxPoint(max) {}
    [[nodiscard]] Coord getMinPoint() const { return minPoint; }
    [[nodiscard]] Coord getMaxPoint() const { return maxPoint; }
    [[nodiscard]] double getTop() const { return maxPoint.getY(); }
    [[nodiscard]] double getLeft() const { return minPoint.getX(); }
    [[nodiscard]] double getBottom() const { return minPoint.getY(); }
    [[nodiscard]] double getRight() const { return maxPoint.getX(); }
    double getHeight() const;
    double getWidth() const;
    Coord getCenter();
    RectByCoords& operator=(const RectByCoords& r);
    [[nodiscard]] bool isValid() const override;
    [[nodiscard]] bool contain(const Coord& coord) const;
};


class DoubleCircle : public Validator {
    double innerRad, outterRad;
public:
    DoubleCircle() : innerRad(0), outterRad(0) {}
    DoubleCircle(double innerR, double outterR) : innerRad(innerR), outterRad(outterR) {}
    [[nodiscard]] double getInnerRad() const { return innerRad; }
    [[nodiscard]] double getOutterRad() const { return outterRad; }
    [[nodiscard]] bool isValid() const override;
    bool operator<(const DoubleCircle& dc) const { return outterRad < dc.outterRad; }
    bool operator>(const DoubleCircle& dc) const { return outterRad > dc.outterRad; }
};