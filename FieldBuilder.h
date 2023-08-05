#pragma once
#include "Geometry.h"
#include "Objects.h"
#include <vector>
#include <map>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

enum Direction {
	RIGHT, DOWN, LEFT, UP
};

class FieldBuilder {
	Rect baseField;
	vector<Rect> obstructions;
	
	Coord getCenterCoord(Direction dir, Rect &checkingField, Bolt b, bool first);
	void shiftBoltCenter(Direction dir, Rect obstruction, Bolt &b);
	Rect narrowedFirstField(vector<Bolt> &currentLevel);
	Rect narrowedNextField(vector<Bolt> &currentLevel, Rect &field);
	bool narrowField(Rect &checkingField, vector<Bolt> &currentLevel, bool &first);
	bool doubleTryForCentering(Direction dir, Rect& checkingField, vector<Rect>& obstructionsToCheck, Bolt& b);
	bool putOneInCenter(Rect &checkingField, vector<Rect> &obstructionsToCheck, Bolt &b);
	bool putTwoInCenter(Rect& checkingField, vector<Rect>& obstructionsToCheck, Bolt& less, Bolt& more);
public:
	
	vector<Bolt> bolts; // вернуть в приват
	FieldBuilder(Rect field) : baseField(field) {}
	void setObstruction(Rect rect);
	void addBolt(Bolt bolt);
	bool build();
	void showInfo() { baseField.showInfo(); } // на удаление
	
};

