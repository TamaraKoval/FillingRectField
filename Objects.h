#pragma once
#include "Geometry.h"
#include <vector>

using namespace std;

class Bolt {
	DoubleCircle head;
	Coord center;
	vector<Coord> innerVertices, outterVertices;
	void setVertices(int rad, vector<Coord> &v);

public:
	Bolt() { setCenter(center); }
	Bolt(DoubleCircle circle) : head(circle), center(0, 0) { setCenter(center); }
	bool setCenter(Coord coord);
	Coord& getCenter() { return center; }
	int getInnerRad() { return head.getInnerRad(); }
	int getOutterRad() { return head.getOutterRad(); }
	bool operator<(Bolt b) { return head < b.head; }
	bool isValid();
	int calcPotencial() { return head.getInnerRad() + head.getOutterRad(); } // may delete
	bool allInside(Rect field);
	bool intersect(Rect rect);
	Rect turnIntoRect();
	void showInfo(); // на удаление (+инклуд)
};

