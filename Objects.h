#pragma once
#include "Geometry.h"
#include <vector>

using std::vector;

class Obstruction : public Validator {
    RectByCoords borders;
    bool hard = false;
public:
    Obstruction() = default;
    Obstruction(const RectByCoords& borders, bool hard) : borders(borders), hard(hard) {}
    explicit Obstruction(const RectByCoords& borders) : borders(borders) {}
    [[nodiscard]] RectByCoords getBorders() const { return borders; }
    [[nodiscard]] bool isHard() const { return hard; }
    [[nodiscard]] bool isValid() const override;
};

class Bolt : public Validator {
    DoubleCircle head;
    Coord center;
    int id;
    vector<Coord> innerVertices, outterVertices;
    void enteringAxialVertices(double leg, vector<Coord>& v);
    void enteringVertices(double leg1, double leg2, vector<Coord>& v);
    void setVertices(double rad, vector<Coord>& v);
public:
    Bolt() = default;
    Bolt(DoubleCircle circle, int i = 0) : head(std::move(circle)), center(0, 0), id(i) {}
    void setCenter(Coord coord);
    [[nodiscard]] Coord getCenter() const { return center; }
    [[nodiscard]] double getInnerRad() const { return head.getInnerRad(); }
    [[nodiscard]] double getOutterRad() const { return head.getOutterRad(); }
    [[nodiscard]] int getID() const { return id; }
    bool operator<(const Bolt& b) const { return head < b.head; }
    bool operator>(const Bolt& b) const { return head > b.head; }
    [[nodiscard]] bool isValid() const override;
    double calcPotencial();
    bool outterCircleInside(const RectByCoords& field);
    bool innerCircleInside(const RectByCoords& field);
    bool allInside(const RectByCoords& field, bool checkInner = true);
    bool intersect(const Obstruction& obstruction);
    RectByCoords turnIntoRect();
    void showInfo(); // на удаление (+инклуд)
};