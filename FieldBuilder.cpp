#include "FieldBuilder.h"

void nextDir(Direction &dir) {
	int curr = (int)dir;
	curr++;
	curr %= 4;
	dir = static_cast<Direction>(curr);
}

Coord FieldBuilder::getCenterCoord(Direction dir, Rect &checkingField, Bolt b, bool first) {
	Coord center;
	int rad = first ? b.getInnerRad() : b.getOutterRad();
	switch (dir) {
		case RIGHT:
			center.SetCoord(checkingField.getLeft() + rad, checkingField.getTop() - rad);
			break;
		case DOWN:
			center.SetCoord(checkingField.getRight() - rad, checkingField.getTop() - rad);
			break;
		case LEFT:
			center.SetCoord(checkingField.getRight() - rad, checkingField.getBottom() + rad);
			break;
		case UP:
			center.SetCoord(checkingField.getLeft() + rad, checkingField.getBottom() + rad);
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

Rect FieldBuilder::narrowedFirstField(vector<Bolt> &currentLevel) {
	int maxPotencial = 0;
	for (Bolt b : currentLevel) {
		if (b.calcPotencial() > maxPotencial) maxPotencial = b.calcPotencial();
	}
	Coord potencialCoord(maxPotencial, maxPotencial);
	currentLevel.clear();
	return Rect(baseField.getMinPoint() + potencialCoord, baseField.getMaxPoint() - potencialCoord);
}

Rect FieldBuilder::narrowedNextField(vector<Bolt> &currentLevel, Rect &field) {
	int shift = currentLevel[0].getOutterRad();
	Coord shiftedValue(shift, shift);
	currentLevel.clear();
	return Rect(field.getMinPoint() + shiftedValue, field.getMaxPoint() - shiftedValue);
}

bool FieldBuilder::narrowField(Rect &checkingField, vector<Bolt> &currentLevel, bool &first) {
	checkingField = first ? narrowedFirstField(currentLevel) : narrowedNextField(currentLevel, checkingField);
	first = false;
	return checkingField.isValid();
}

bool FieldBuilder::doubleTryForCentering(Direction dir, Rect& checkingField, vector<Rect>& obstructionsToCheck, Bolt& b) {
	int experiment = 2;
	while (experiment) {
		if (!b.allInside(checkingField)) return false;
		experiment--;
		for (int i = 0; i < obstructionsToCheck.size(); i++) {
			if (b.intersect(obstructionsToCheck[i])) {
				shiftBoltCenter(dir, obstructionsToCheck[i], b);
				if (!experiment) return false;
				break;
			}
		}
	}
	return true;
}

bool FieldBuilder::putOneInCenter(Rect &checkingField, vector<Rect> &obstructionsToCheck, Bolt &b) {
	b.setCenter(checkingField.getCenter());
	return doubleTryForCentering(RIGHT, checkingField, obstructionsToCheck, b);
}

bool FieldBuilder::putTwoInCenter(Rect &checkingField, vector<Rect> &obstructionsToCheck, Bolt &less, Bolt &more) {
	Coord lessCenter, moreCenter;
	Coord center = checkingField.getCenter();
	lessCenter = moreCenter = center;
	lessCenter.SetX(center.getX() - less.getOutterRad());
	less.setCenter(lessCenter);
	if (doubleTryForCentering(LEFT, checkingField, obstructionsToCheck, less)) {
		moreCenter.SetX(center.getX() + more.getOutterRad());
		more.setCenter(moreCenter);
		return doubleTryForCentering(RIGHT, checkingField, obstructionsToCheck, more);
	}
	return false;
}

void FieldBuilder::setObstruction(Rect rect) {
	if (rect.isValid()) obstructions.push_back(rect);
}

void FieldBuilder::addBolt(Bolt bolt) {
	if (bolt.isValid()) bolts.push_back(bolt);
}

bool FieldBuilder::build() {
	if (!baseField.isValid() || bolts.empty()) return false;

	sort(bolts.begin(), bolts.end());
	vector<Rect> obstructionsToCheck(obstructions.size());
	copy(obstructions.begin(), obstructions.end(), obstructionsToCheck.begin());

	enum Direction dir = RIGHT;

	Rect checkingField = baseField;
	bool firstNarrow = true;
	int blockedSidesCount = 0;
	vector<Bolt> currentLevel;

	bool boltState;

	for (int i = 0; i < bolts.size(); i++) {
		boltState = false;

		if (currentLevel.empty() && (bolts.size() - i) < 3) {
			if ((bolts.size() - i) == 2) {
				if (putTwoInCenter(checkingField, obstructionsToCheck, bolts[i + 1], bolts[i])) break;
			} else {
				if (putOneInCenter(checkingField, obstructionsToCheck, bolts[i])) break;
			}
		} 

		while (!boltState) {
			bolts[i].setCenter(getCenterCoord(dir, checkingField, bolts[i], firstNarrow));
			if (!bolts[i].allInside(checkingField)) return false;

			for (int j = 0; j < obstructionsToCheck.size(); j++) {
				if (bolts[i].intersect(obstructionsToCheck[j])) {
					shiftBoltCenter(dir, obstructionsToCheck[j], bolts[i]);
					if (!bolts[i].allInside(checkingField)) {
						blockedSidesCount++;
						if (blockedSidesCount == 4) {
							if (!narrowField(checkingField, currentLevel, firstNarrow)) return false;
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
