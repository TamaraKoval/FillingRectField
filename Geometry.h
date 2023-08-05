#pragma once
#include <ostream>
#include <iostream>

class Coord {
    int x, y;
public:
    Coord() { x = 0; y = 0; }
    Coord(int xx, int yy) : x(xx), y(yy) {}
    void SetCoord(int xx, int yy) { x = xx; y = yy; }
    void SetX(int xx) { x = xx; }
    void SetY(int yy) { y = yy; }
    [[nodiscard]] int getX() const { return x; }
    [[nodiscard]] int getY() const { return y; }
    Coord& operator=(Coord c);
    Coord operator+(Coord c) const;
    Coord operator-(Coord c) const;
    friend std::ostream& operator<<(std::ostream& stream, Coord& coords);
};

class Figure {
public:
    virtual bool isValid() = 0;
};

class Rect : public Figure {
    Coord minPoint, maxPoint;
public:
    Rect() = default;
    Rect(Coord min, Coord max) : minPoint(min), maxPoint(max) {}
    Coord getMinPoint() { return minPoint; }
    Coord getMaxPoint() { return maxPoint; }
    int getTop() { return maxPoint.getY(); }
    int getLeft() { return minPoint.getX(); }
    int getBottom() { return minPoint.getY(); }
    int getRight() { return maxPoint.getX(); }
    Coord getCenter();
    Rect& operator=(const Rect& r);
    void showInfo() { std::cout << "Ќижний угол: " << minPoint << ", верхний угол: " << maxPoint; } // на удаление (+инклуд)
    bool isValid() override;
    [[nodiscard]] bool contain(Coord coord) const;
};

class DoubleCircle : public Figure {
    int innerRad, outterRad;
public:
    DoubleCircle() : innerRad(0), outterRad(0) {}
    DoubleCircle(int innerR, int outterR) : innerRad(innerR), outterRad(outterR) {}
    void showInfo() const { std::cout << "¬нутренний r: " << innerRad << ", внешний r: " << outterRad; } // на удаление (+инклуд)
    [[nodiscard]] int getInnerRad() const { return innerRad; }
    [[nodiscard]] int getOutterRad() const { return outterRad; }
    bool isValid() override;
    bool operator<(const DoubleCircle& dc) const { return outterRad < dc.outterRad; }
    bool operator>(const DoubleCircle& dc) const { return outterRad > dc.outterRad; }
};

