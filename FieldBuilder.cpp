#include "FieldBuilder.h"

void nextDir(Direction &dir) {
	int curr = (int)dir;
	curr++;
	curr %= 4;
	dir = static_cast<Direction>(curr);
}

void FieldBuilder::prepareData(vector<Rect> &v) {
	sort(bolts.begin(), bolts.end());
	copy(obstructions.begin(), obstructions.end(), v.begin());
}

Coord FieldBuilder::getOriginalCenter(Direction dir, Bolt b, bool firstLevel) { // переделать, если не в первый раз
	Coord center;
	switch (dir) {
		case RIGHT:
			center.SetCoord(checkingField.getLeft() + b.getInnerRad(), checkingField.getTop() - b.getInnerRad());
			break;
		case DOWN:
			center.SetCoord(checkingField.getRight() - b.getInnerRad(), checkingField.getTop() - b.getInnerRad());
			break;
		case LEFT:
			center.SetCoord(checkingField.getRight() - b.getInnerRad(), checkingField.getBottom() + b.getInnerRad());
			break;
		case UP:
			center.SetCoord(checkingField.getLeft() + b.getInnerRad(), checkingField.getBottom() + b.getInnerRad());
	}
	return center;
}

void FieldBuilder::shiftBoltCenter(Direction dir, Rect obstruction, Bolt &b) {
	Coord center = b.getCenter();
	int shift = b.getInnerRad();

	switch (dir) {
		case RIGHT:
			center.SetX(obstruction.getRight() + shift);
			break;
		case DOWN:
			center.SetY(obstruction.getBottom() - shift);
			break;
		case LEFT:
			center.SetX(obstruction.getLeft() - shift);
			break;
		case UP:
			center.SetY(obstruction.getTop() + shift);
	}
	b.setCenter(center);
}

Rect FieldBuilder::narrowFirstField(vector<Bolt> &currentLevel) { // ? может булев параметр и аргумент по умолчанию
	int maxPotencial = 0;
	for (Bolt b : currentLevel) {
		if (b.calcPotencial() > maxPotencial) maxPotencial = b.calcPotencial();
	}
	Coord potencialCoord(maxPotencial, maxPotencial);
	currentLevel.clear();
	return Rect(baseField.getMinPoint() + potencialCoord, baseField.getMaxPoint() - potencialCoord);
}

Rect FieldBuilder::narrowField(vector<Bolt> &currentLevel, Rect& field) {
	int shift = currentLevel[0].getOutterRad();
	Coord shiftedValue(shift, shift);
	currentLevel.clear();
	return Rect(field.getMinPoint() + shiftedValue, field.getMaxPoint() - shiftedValue);
}

void FieldBuilder::setObstruction(Rect rect) {
	if (rect.isValid()) obstructions.push_back(rect);
}

void FieldBuilder::addBolt(Bolt bolt) {
	if (bolt.isValid()) bolts.push_back(bolt);
}

bool FieldBuilder::build() {
	if (!baseField.isValid() || bolts.empty()) return false;

	vector<Rect> obstructionsToCheck(obstructions.size());
	prepareData(obstructionsToCheck);

	enum Direction dir = RIGHT;

	Rect checkingField = baseField;
	bool firstNarrow = true;
	int blockedSidesCount = 0;
	vector<Bolt> currentLevel;

	bool boltState;

	for (int i = 0; i < bolts.size(); i++) {
		boltState = false;
		while (!boltState) {
			bolts[i].setCenter(getOriginalCenter(dir, checkingField, bolts[i])); // а если было сужение? то надо ориентироваться на внешний радиус
			if (bolts[i].allInside(checkingField)) return false;

			for (int j = 0; j < obstructionsToCheck.size(); j++) { // убрать
				if (bolts[i].intersect(obstructionsToCheck[j])) {
					shiftBoltCenter(dir, obstructionsToCheck[j], bolts[i]);
					if (bolts[i].allInside(checkingField)) {
						blockedSidesCount++;
						if (blockedSidesCount == 4) {
							checkingField = firstNarrow ? narrowFirstField(currentLevel) : narrowField(currentLevel, checkingField);
						}
						nextDir(dir);
						break;
					}
					j = -1;
				}
			}
			boltState = true;
			obstructionsToCheck.push_back(bolts[i].turnIntoRect());
			currentLevel.push_back(bolts[i]);
			nextDir(dir);
		}
	}
	return true;
}
