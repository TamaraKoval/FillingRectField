#include "Objects.h"

void Bolt::setVertices(int rad, std::vector<Coord>& v) {
    v.emplace_back(center.getX() - rad, center.getY());
    v.emplace_back(center.getX() + rad, center.getY());
    v.emplace_back(center.getX(), center.getY() - rad);
    v.emplace_back(center.getX(), center.getY() + rad);

    int leg = (int)(sqrt(rad ^ 2 / 2));
    leg++;
    v.emplace_back(center.getX() - leg, center.getY() - leg);
    v.emplace_back(center.getX() - leg, center.getY() + leg);
    v.emplace_back(center.getX() + leg, center.getY() - leg);
    v.emplace_back(center.getX() + leg, center.getY() + leg);
}

void Bolt::setCenter(Coord coord) {
    center = coord;
    setVertices(head.getInnerRad(), innerVertices);
    setVertices(head.getOutterRad(), outterVertices);
}

bool Bolt::isValid() {
    return head.isValid();
}

bool Bolt::outterCircleInside(const Rect& field) {
    for (Coord c : outterVertices) {
        if (!field.contain(c)) return false;
    }
    return innerCircleInside(field);
}

bool Bolt::innerCircleInside(const Rect& field) {
    if (!field.contain(center)) return false;
    for (Coord c : innerVertices) {
        if (!field.contain(c)) return false;
    }
    return true;
}

bool Bolt::allInside(const Rect& field, bool checkInner) {
    if (checkInner) return innerCircleInside(field);
    return outterCircleInside(field);
}

bool Bolt::intersect(const Obstruction& rect) {
    return !allInside(rect, !rect.isHard());
}

Rect Bolt::turnIntoRect() {
    Coord min(center.getX() - head.getOutterRad(), center.getY() - head.getOutterRad());
    Coord max(center.getX() + head.getOutterRad(), center.getY() + head.getOutterRad());
    Rect temp(min, max);
    return temp;
}

void Bolt::showInfo() {
    std::cout << "Внутренний r: " << head.getInnerRad() << ", внешний r: " << head.getOutterRad() <<
        ". Центр: " << center << std::endl;
}

