#pragma once
#include "Geometry.h"
#include "Objects.h"
#include <utility>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

enum Direction {
    RIGHT, DOWN, LEFT, UP
};

class FieldBuilder {
    Rect baseField;
    vector<Obstruction> obstructions;

    static void setCenterCoord(Direction dir, Rect& checkingField, Bolt& b, bool first);
    static void shiftBoltCenter(Direction dir, Obstruction& obstruction, Bolt& b);
    Rect narrowedFirstField(vector<Bolt>& currentLevel);
    static Rect narrowedNextField(vector<Bolt>& currentLevel, Rect& field);
    bool narrowField(Rect& checkingField, vector<Bolt>& currentLevel, bool& first);
    static bool doubleTryForCentering(Direction dir, Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first);
    static bool putOneInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& b, bool first);
    static bool putTwoInCenter(Rect& checkingField, vector<Obstruction>& obstructionsToCheck, Bolt& less, Bolt& more, bool first);
public:

    vector<Bolt> installedBolts; // вернуть в приват
    vector<Bolt> bolts;

    explicit FieldBuilder(const Rect& field) : baseField(field) {}
    void setObstruction(Obstruction rect);
    void addBolt(Bolt bolt);
    bool build();
};

