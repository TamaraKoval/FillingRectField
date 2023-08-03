#pragma once
#include "Geometry.h"
#include "Objects.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

enum Direction {
	RIGHT, DOWN, LEFT, UP
};

class FieldBuilder {
	Rect baseField;
	vector<Rect> obstructions;
	vector<Bolt> bolts;
	void prepareData(vector<Rect> &v);
	Coord getOriginalCenter(Direction dir, Rect checkingField, Bolt b);
	void shiftBoltCenter(Direction dir, Rect obstruction, Bolt &b);
	Rect narrowFirstField(vector<Bolt>& currentLevel);
	Rect narrowField(vector<Bolt>& currentLevel, Rect& field);
public:
	FieldBuilder(Rect field) : baseField(field) {}
	void setObstruction(Rect rect);
	void addBolt(Bolt bolt);
	bool build();
	void showInfo() { baseField.showInfo(); }

};

