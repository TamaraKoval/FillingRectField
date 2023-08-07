#pragma once
#include "Geometry.h"
#include "Objects.h"
#include <vector>
#include <algorithm>

using std::vector;

enum Direction {
    RIGHT, DOWN, LEFT, UP
};

class FieldBuilder {
    RectByCoords baseField;
    vector<Obstruction> obstructions;
    vector<Bolt> bolts;
    vector<Bolt> installedBolts;
    static void setCenterCoord(Direction& dir, RectByCoords& checkingField, Bolt& b, bool first);
    static void shiftBoltCenter(Direction& dir, Obstruction& obstruction, Bolt& b);
    RectByCoords narrowedFirstField(vector<Bolt>& currentLevel, bool& first);
    static RectByCoords narrowedNextField(vector<Bolt>& currentLevel, RectByCoords& field);
    bool narrowField(RectByCoords& checkingField, vector<Bolt>& currentLevel, bool& first, int& blockedSidesCount);
    static bool
        doubleTryForCentering(Direction dir, RectByCoords& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first);
    static bool putOneInCenter(RectByCoords& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first);
    static bool putTwoInCenter(RectByCoords& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& less, Bolt& more, bool first);
public:
    explicit FieldBuilder(const RectByCoords& field) : baseField(field) {}
    void setObstruction(const Obstruction& rect);
    void addBolt(const Bolt& bolt);
    bool build();
    [[nodiscard]] RectByCoords getbasefield() const { return baseField; }
    [[nodiscard]] vector<Obstruction> getObstructions() const { return obstructions; }
    [[nodiscard]] vector<Bolt> getInstalledBolts() const { return installedBolts; }
};