#include <iostream>
#include "Objects.h"

bool Obstruction::isValid() const {
    return borders.isValid();
}

void Bolt::enteringAxialVertices(double leg, vector<Coord>& v) {
    v.emplace_back(center.getX(), center.getY() + leg);
    v.emplace_back(center.getX() + leg, center.getY());
    v.emplace_back(center.getX(), center.getY() - leg);
    v.emplace_back(center.getX() - leg, center.getY());
}

void Bolt::enteringVertices(double leg1, double leg2, vector<Coord>& v) {
    v.emplace_back(center.getX() + leg1, center.getY() + leg2);
    v.emplace_back(center.getX() + leg1, center.getY() - leg2);
    v.emplace_back(center.getX() - leg1, center.getY() - leg2);
    v.emplace_back(center.getX() - leg1, center.getY() + leg2);
}

void Bolt::setVertices(double rad, vector<Coord>& v) {
    enteringAxialVertices(rad, v);

    double leg45 = sqrt(pow(rad, 2) / 2);
    enteringVertices(leg45, leg45, v);

    double leg30X = rad / 2;
    double leg30Y = sqrt(pow(rad, 2) - pow(leg30X, 2));
    enteringVertices(leg30X, leg30Y, v);
    enteringVertices(leg30Y, leg30X, v);
}

void Bolt::setCenter(Coord coord) {
    center = coord;
    innerVertices.clear();
    setVertices(head.getInnerRad() , innerVertices);
    outterVertices.clear();
    setVertices(head.getOutterRad(), outterVertices);
}

bool Bolt::isValid() const {
    return head.isValid();
}

double Bolt::calcPotencial() {
    return head.getInnerRad()  + head.getOutterRad() ;
}

bool Bolt::outterCircleInside(const Rect& field) {
    for (Coord c : outterVertices) {
        if (!field.contain(c)) return false;
    }
    return innerCircleInside(field);
}

bool Bolt::innerCircleInside(const Rect& field) {
    for (Coord c : innerVertices) {
        if (!field.contain(c)) return false;
    }
    return true;
}

bool Bolt::allInside(const Rect& field, bool checkInner) {
    if (!field.contain(center)) return false;
    if (checkInner) return innerCircleInside(field);
    return outterCircleInside(field);
}

bool Bolt::intersect(const Obstruction& obstruction) {
    Rect rect = obstruction.getBorders();
    if (rect.contain(center)) return true;
    if (obstruction.isHard()) {
        for (Coord c : outterVertices) {
            if (rect.contain(c)) return true;
        }
    }
    for (Coord c : innerVertices) {
        if (rect.contain(c)) return true;
    }
    return false;
}

Rect Bolt::turnIntoRect() {
    double shift = head.getOutterRad();
    Coord min(center.getX() - shift, center.getY() - shift);
    Coord max(center.getX() + shift, center.getY() + shift);
    return { min, max };
}

void Bolt::showInfo() {
    std::cout << "���������� r: " << head.getInnerRad() << ", ������� r: " << head.getOutterRad() <<
        ". �����: " << center << std::endl;
}

