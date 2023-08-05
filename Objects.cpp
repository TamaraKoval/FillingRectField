#include "Objects.h"

void Bolt::setVertices(int rad, std::vector<Coord> &v) {
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

void Bolt::setCenter(Coord coord) {
	center = coord;
	setVertices(head.getInnerRad(), innerVertices);
	setVertices(head.getOutterRad(), outterVertices);
}

bool Bolt::isValid() {
	return head.isValid();
}

bool Bolt::allInside(Rect field) {
	for (Coord c : innerVertices) {
		if (!field.contain(c)) return false;
	}
	return true;
}

bool Bolt::intersect(Rect rect) {
	return !allInside(rect);
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

