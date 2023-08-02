#include "Objects.h"

void Bolt::setVertices(int rad, vector<Coord> &v) {
	v.push_back(Coord(center.getX() - rad, center.getY()));
	v.push_back(Coord(center.getX() + rad, center.getY()));
	v.push_back(Coord(center.getX(), center.getY() - rad));
	v.push_back(Coord(center.getX(), center.getY() + rad));

	int leg = (int)(sqrt(rad^2 / 2));
	leg++;
	v.push_back(Coord(center.getX() - leg, center.getY() - leg));
	v.push_back(Coord(center.getX() - leg, center.getY() + leg));
	v.push_back(Coord(center.getX() + leg, center.getY() - leg));
	v.push_back(Coord(center.getX() + leg, center.getY() + leg));
}

bool Bolt::isValid() {
	return head.isValid();
}

bool Bolt::setCenter(Coord coord) {
	if (outterVertices.empty()) {
		center = coord;
		setVertices(head.getInnerRad(), innerVertices);
		setVertices(head.getOutterRad(), outterVertices);
		return true;
	}
	return false;
}

void Bolt::resetCenter() {
	center.SetCoord(0, 0);
	outterVertices.clear();
	innerVertices.clear();
}

Rect Bolt::turnIntoRect() {
	Coord min(center.getX() - head.getOutterRad(), center.getY() - head.getOutterRad());
	Coord max(center.getX() + head.getOutterRad(), center.getY() + head.getOutterRad());
	Rect temp(min, max);
	return temp;
}

bool Bolt::allInside(Rect field) {
	Coord newMin(field.getMinPoint().getX() + 1, field.getMinPoint().getY() + 1);
	Coord newMax(field.getMaxPoint().getX() - 1, field.getMaxPoint().getY() - 1);
	Rect temp(newMin, newMax);
	for (Coord c : innerVertices) {
		if (!temp.contain(c)) return false;
	}
	return true;
}

bool Bolt::intersect(Rect rect) {
	return !allInside(rect);
}

bool Bolt::intersect(Bolt b) {
	Rect temp = b.turnIntoRect();
	return	intersect(temp);
}

void Bolt::showInfo() {
	std::cout << "Внутренний r: " << head.getInnerRad() << ", внешний r: " << head.getOutterRad() <<
		". Центр: " << center << endl;
}

