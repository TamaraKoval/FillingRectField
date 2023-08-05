#include "FieldBuilder.h"

void nextDir(Direction& dir) {
    int curr = (int)dir;
    curr++;
    curr %= 4;
    dir = static_cast<Direction>(curr);
}

void FieldBuilder::setCenterCoord(Direction dir, Rect& checkingField, Bolt& b, bool first) {
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
    b.setCenter(center);
}

void FieldBuilder::shiftBoltCenter(Direction dir, Obstruction& obstruction, Bolt& b) {
    Coord center = b.getCenter();
    int shift = obstruction.isHard() ? b.getOutterRad() : b.getInnerRad();

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

Rect FieldBuilder::narrowedFirstField(vector<Bolt>& currentLevel) {
    int maxPotencial = 0;
    for (Bolt b : currentLevel) {
        if (b.calcPotencial() > maxPotencial) maxPotencial = b.calcPotencial();
    }
    Coord potencialCoord(maxPotencial, maxPotencial);
    currentLevel.clear();
    return { baseField.getMinPoint() + potencialCoord, baseField.getMaxPoint() - potencialCoord };
}

Rect FieldBuilder::narrowedNextField(vector<Bolt>& currentLevel, Rect& field) {
    int shift = max_element(currentLevel.begin(), currentLevel.end())->getOutterRad();
    Coord shiftedValue(shift, shift);
    currentLevel.clear();
    return { field.getMinPoint() + shiftedValue, field.getMaxPoint() - shiftedValue };
}

bool FieldBuilder::narrowField(Rect& checkingField, vector<Bolt>& currentLevel, bool& first) {
    checkingField = first ? narrowedFirstField(currentLevel) : narrowedNextField(currentLevel, checkingField);
    first = false;
    return checkingField.isValid();
}

bool FieldBuilder::doubleTryForCentering(Direction dir, Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first) {
    int experiment = 2;
    while (experiment) {
        if (!b.allInside(checkingField, first)) return false;
        experiment--;
        for (Obstruction& obs : obstructionsToCheck) {
            if (b.intersect(obs)) {
                if (!experiment) return false;
                shiftBoltCenter(dir, obs, b);
                break;
            }
        }
    }
    return true;
}

bool FieldBuilder::putOneInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first) {
    b.setCenter(checkingField.getCenter());
    return doubleTryForCentering(RIGHT, checkingField, obstructionsToCheck, b, first);
}

bool FieldBuilder::putTwoInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& less, Bolt& more, bool first) {
    Coord lessCenter, moreCenter;
    Coord center = checkingField.getCenter();
    lessCenter = moreCenter = center;
    int lessRad = first ? less.getInnerRad() : less.getOutterRad();
    lessCenter.SetX(center.getX() - lessRad);
    less.setCenter(lessCenter);
    if (doubleTryForCentering(LEFT, checkingField, obstructionsToCheck, less, first)) {
        int moreRad = first ? more.getInnerRad() : more.getOutterRad();
        moreCenter.SetX(center.getX() + moreRad);
        more.setCenter(moreCenter);
        return doubleTryForCentering(RIGHT, checkingField, obstructionsToCheck, more, first);
    }
    return false;
}

void FieldBuilder::setObstruction(Obstruction rect) {
    if (rect.isValid()) obstructions.push_back(rect);
}

void FieldBuilder::addBolt(Bolt bolt) {
    if (bolt.isValid()) bolts.push_back(bolt);
}

bool FieldBuilder::build() {
    if (!baseField.isValid() || bolts.empty()) return false;

    sort(bolts.begin(), bolts.end(), [](Bolt& a, Bolt& b) {
        return a > b;
        });
    vector<Bolt> boltsToCheck(bolts.size());
    copy(bolts.begin(), bolts.end(), boltsToCheck.begin());

    vector<Obstruction> obstructionsToCheck(obstructions.size());
    copy(obstructions.begin(), obstructions.end(), obstructionsToCheck.begin());

    enum Direction dir = RIGHT;

    Rect checkingField = baseField;
    bool firstNarrow = true;
    int blockedSidesCount = 0;
    vector<Bolt> currentLevel;

    bool boltState;
    int index;

    while (!boltsToCheck.empty()) {
        index = 0;
        boltState = false;

        if (currentLevel.empty() && boltsToCheck.size() == 2) {
            if (putTwoInCenter(checkingField, obstructionsToCheck, boltsToCheck[1], boltsToCheck[0], firstNarrow)) {
                installedBolts.push_back(boltsToCheck[0]);
                installedBolts.push_back(boltsToCheck[1]);
                boltsToCheck.clear();
                break;
            }
        }
        else if (currentLevel.empty() && boltsToCheck.size() == 1) {
            if (putOneInCenter(checkingField, obstructionsToCheck, boltsToCheck[0], firstNarrow)) {
                installedBolts.push_back(boltsToCheck[0]);
                boltsToCheck.clear();
                break;
            }
        }

        while (!boltState) {
            setCenterCoord(dir, checkingField, boltsToCheck[index], firstNarrow);
            if (!boltsToCheck[index].allInside(checkingField, firstNarrow)) return false;

            bool intersectionFound = false;
            for (int j = 0; j < obstructionsToCheck.size(); j++) {
                if (boltsToCheck[index].intersect(obstructionsToCheck[j])) {
                    shiftBoltCenter(dir, obstructionsToCheck[j], boltsToCheck[index]);
                    if (!boltsToCheck[index].allInside(checkingField, firstNarrow)) {
                        blockedSidesCount++;
                        if (blockedSidesCount == 4) {
                            if (!narrowField(checkingField, currentLevel, firstNarrow)) return false;
                        }
                        nextDir(dir);
                        break;
                    }
                    intersectionFound = true;
                }
                if (!intersectionFound) j--;
            }
            boltState = true;
            installedBolts.push_back(boltsToCheck[0]);
            obstructionsToCheck.emplace_back(boltsToCheck[index].turnIntoRect(), true);
            currentLevel.push_back(boltsToCheck[index]);
            boltsToCheck.erase(boltsToCheck.begin());
            nextDir(dir);
        }
    }
    return true;
}
