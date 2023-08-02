#pragma once
#include "Geometry.h"
#include <vector>

using namespace std;


class Bolt {
	DoubleCircle head;
	Coord center;

	void setVertices(int rad, vector<Coord> &v);
public:
	Bolt() {}
	Bolt(DoubleCircle circle) : head(circle), center(0, 0) {}
	vector<Coord> innerVertices; // вернуть в приват
	vector<Coord> outterVertices; // вернуть в приват
	bool isValid();
	bool setCenter(Coord coord);
	void resetCenter();
	Coord& getCenter() { return center; }
	bool operator<(Bolt b) { return head < b.head; }
	int calcPotencial() { return head.getInnerRad() + head.getOutterRad(); }
	Rect turnIntoRect();
	bool allInside(Rect field);
	bool intersect(Rect rect);
	bool intersect(Bolt b);
	void showInfo(); // на удаление (+инклуд)
};

