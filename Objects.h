#pragma once
#include "Geometry.h"
#include <vector>

using std::vector;

class Obstruction : public Validator {
    Rect borders;
    bool hard = false;
public:
    Obstruction() = default;
    Obstruction(const Rect& borders, bool hard) : borders(borders), hard(hard) {}
    explicit Obstruction(const Rect& borders) : borders(borders) {}
    [[nodiscard]] Rect getBorders() const { return borders; }
    [[nodiscard]] bool isHard() const { return hard; }
    [[nodiscard]] bool isValid() const override;
};

class Bolt : public Validator {
    DoubleCircle head;
    Coord center;
    vector<Coord> innerVertices, outterVertices;
    void enteringAxialVertices(double leg, vector<Coord>& v);
    void enteringVertices(double leg1, double leg2, vector<Coord>& v);
    void setVertices(double rad, vector<Coord>& v);
public:
    Bolt() = default;
    explicit Bolt(DoubleCircle circle) : head(std::move(circle)), center(0, 0) {}
    void setCenter(Coord coord);
    [[nodiscard]] Coord getCenter() const { return center; }
    [[nodiscard]] double getInnerRad() const { return head.getInnerRad(); }
    [[nodiscard]] double getOutterRad() const { return head.getOutterRad(); }
    bool operator<(const Bolt& b) const { return head < b.head; }
    bool operator>(const Bolt& b) const { return head > b.head; }
    [[nodiscard]] bool isValid() const override;
    double calcPotencial();
    bool outterCircleInside(const Rect& field);
    bool innerCircleInside(const Rect& field);
    bool allInside(const Rect& field, bool checkInner = true);
    bool intersect(const Obstruction& obstruction);
    Rect turnIntoRect();
    void showInfo(); // на удаление (+инклуд)
};

