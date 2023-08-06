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
    Rect baseField;
    vector<Obstruction> obstructions;
    vector<Bolt> bolts;
    vector<Bolt> installedBolts;
    static void setCenterCoord(Direction& dir, Rect& checkingField, Bolt& b, bool first);
    static void shiftBoltCenter(Direction& dir, Obstruction& obstruction, Bolt& b);
    Rect narrowedFirstField(vector<Bolt>& currentLevel, bool& first);
    static Rect narrowedNextField(vector<Bolt>& currentLevel, Rect& field);
    bool narrowField(Rect& checkingField, vector<Bolt>& currentLevel, bool& first, int& blockedSidesCount);
    static bool
        doubleTryForCentering(Direction dir, Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first);
    static bool putOneInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first);
    static bool putTwoInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& less, Bolt& more, bool first);
public:
    explicit FieldBuilder(const Rect& field) : baseField(field) {}
    void setObstruction(const Obstruction& rect);
    void addBolt(const Bolt& bolt);
    bool build();
    [[nodiscard]] vector<Bolt> getInstalledBolts() const { return installedBolts; }
};

