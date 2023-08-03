#include <iostream>
#include "Geometry.h"
#include "Objects.h"
#include "FieldBuilder.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    
    // Coord
    Coord a(1, 1), b(6, 6);
    Coord o;
    Coord x(3, 3);

    // Rect
    Rect r1(a, b);

    // DoubleCircle
    DoubleCircle c1;
    DoubleCircle c2(1, 2), c3(2, 4);

    // Bolt
    Bolt bolt1;
    Bolt bolt2(c2), bolt3(c3);

    FieldBuilder field(r1);
    field.addBolt(bolt2);
    field.addBolt(bolt3);
    field.addBolt(bolt1);
    //for (Bolt i : field.bolts)  i.showInfo();
    cout << endl;
    field.build();
    //for (Bolt i : field.bolts)  i.showInfo();


    return 0;
}