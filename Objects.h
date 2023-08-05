#pragma once
#include "Geometry.h"
#include <utility>
#include <vector>

class Obstruction : public Rect {
    Rect borders;
    bool hard = false;
public:
    Obstruction() = default;
    Obstruction(const Rect& borders, bool hard) : borders(borders), hard(hard) {}
    explicit Obstruction(const Rect& borders) : borders(borders), hard(false) {}
    [[nodiscard]] bool isHard() const { return hard; }
    bool isValid() override { return Rect::isValid(); }
};

class Bolt {
    DoubleCircle head;
    Coord center;
    std::vector<Coord> innerVertices, outterVertices;
    void setVertices(int rad, std::vector<Coord>& v);
public:
    Bolt() = default;
    explicit Bolt(DoubleCircle circle) : head(std::move(circle)) { }
    void setCenter(Coord coord);
    Coord& getCenter() { return center; }
    int getInnerRad() { return head.getInnerRad(); }
    int getOutterRad() { return head.getOutterRad(); }
    bool operator<(const Bolt& b) { return head < b.head; }
    bool operator>(const Bolt& b) { return head > b.head; }
    bool isValid();
    int calcPotencial() { return head.getInnerRad() + head.getOutterRad(); }
    bool outterCircleInside(const Rect& field);
    bool innerCircleInside(const Rect& field);
    bool allInside(const Rect& field, bool checkInner = true);
    bool intersect(const Obstruction& rect);
    Rect turnIntoRect();
    void showInfo(); // на удаление (+инклуд)
};

