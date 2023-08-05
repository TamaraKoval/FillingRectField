#pragma once
#include "Geometry.h"
#include <vector>

class Bolt {
	DoubleCircle head;
	Coord center;
	std::vector<Coord> innerVertices, outterVertices;
	void setVertices(int rad, std::vector<Coord> &v);
public:
	Bolt() { }
	Bolt(DoubleCircle circle) : head(circle) { }
	void setCenter(Coord coord);
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

