#include "FieldBuilder.h"

void nextDir(Direction& dir) {
    int curr = (int)dir;
    curr++;
    curr %= 4;
    dir = static_cast<Direction>(curr);
}

void FieldBuilder::setCenterCoord(Direction& dir, Rect& checkingField, Bolt& b, bool first) {
    Coord center;
    double rad = first ? b.getInnerRad() / 2 : b.getOutterRad() / 2;
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

void FieldBuilder::shiftBoltCenter(Direction& dir, Obstruction& obstruction, Bolt& b) {
    Coord center = b.getCenter();
    double shift = obstruction.isHard() ? b.getOutterRad() / 2 : b.getInnerRad() / 2;
    shift += 0.5;

    switch (dir) {
    case RIGHT:
        center.SetX(obstruction.getBorders().getRight() + shift);
        break;
    case DOWN:
        center.SetY(obstruction.getBorders().getBottom() - shift);
        break;
    case LEFT:
        center.SetX(obstruction.getBorders().getLeft() - shift);
        break;
    case UP:
        center.SetY(obstruction.getBorders().getTop() + shift);
    }
    b.setCenter(center);
}

Rect FieldBuilder::narrowedFirstField(vector<Bolt>& currentLevel, bool& first) {
    double maxPotencial = 0;
    for (Bolt b : currentLevel) {
        if (b.calcPotencial() > maxPotencial) maxPotencial = b.calcPotencial();
    }
    Coord potencialCoord(maxPotencial, maxPotencial);
    first = false;
    return { baseField.getMinPoint() + potencialCoord, baseField.getMaxPoint() - potencialCoord };
}

Rect FieldBuilder::narrowedNextField(vector<Bolt>& currentLevel, Rect& field) {
    double shift = max_element(currentLevel.begin(), currentLevel.end())->getOutterRad();
    Coord shiftedValue(shift, shift);
    return { field.getMinPoint() + shiftedValue, field.getMaxPoint() - shiftedValue };
}

bool FieldBuilder::narrowField(Rect& checkingField, vector<Bolt>& currentLevel, bool& first, int& blockedSidesCount) {
    checkingField = first ? narrowedFirstField(currentLevel, first) : narrowedNextField(currentLevel, checkingField);
    currentLevel.clear();
    blockedSidesCount = 0;
    return checkingField.isValid();
}

bool FieldBuilder::doubleTryForCentering(Direction dir, Rect& checkingField, vector<Obstruction>& obstructionsToCheck,
    Bolt& b, bool first) {
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

bool FieldBuilder::putTwoInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& less, Bolt& more,
    bool first) {
    Coord lessCenter, moreCenter;
    Coord center = checkingField.getCenter();
    lessCenter = moreCenter = center;
    double lessRad = first ? less.getInnerRad() / 2 : less.getOutterRad() / 2;
    lessCenter.SetX(center.getX() - lessRad);
    less.setCenter(lessCenter);
    if (doubleTryForCentering(LEFT, checkingField, obstructionsToCheck, less, first)) {
        double moreRad = first ? more.getInnerRad() / 2 : more.getOutterRad() / 2;
        moreCenter.SetX(center.getX() + moreRad);
        more.setCenter(moreCenter);
        return doubleTryForCentering(RIGHT, checkingField, obstructionsToCheck, more, first);
    }
    return false;
}

void FieldBuilder::setObstruction(const Obstruction& rect) {
    if (rect.isValid()) obstructions.push_back(rect);
}

void FieldBuilder::addBolt(const Bolt& bolt) {
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
        else if (boltsToCheck.size() == 1) {
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
                intersectionFound = false;
                if (boltsToCheck[index].intersect(obstructionsToCheck[j])) {
                    intersectionFound = true;
                    shiftBoltCenter(dir, obstructionsToCheck[j], boltsToCheck[index]);
                    if (!boltsToCheck[index].allInside(checkingField, firstNarrow)) {
                        blockedSidesCount++;
                        if (blockedSidesCount == 4) {
                            if (!narrowField(checkingField, currentLevel, firstNarrow, blockedSidesCount)) return false;
                            nextDir(dir);
                            break;
                        }
                    }
                }
                if (intersectionFound) j = -1;
            }
            if (!intersectionFound) {
                boltState = true;
                installedBolts.push_back(boltsToCheck[index]);
                obstructionsToCheck.emplace_back(boltsToCheck[index].turnIntoRect(), true);
                currentLevel.push_back(boltsToCheck[index]);
                boltsToCheck.erase(boltsToCheck.begin() + index);
                nextDir(dir);
            }
        }
    }
    return true;
}
