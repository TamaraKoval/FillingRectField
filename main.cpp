#include <iostream>
#include "Geometry.h"
#include "Objects.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    
    // Coord
    Coord a(1, 1), b(6, 6);
    Coord o;
    Coord x(3, 3);
    /*
    cout << endl;
    cout << a << endl;
    cout << b << endl;
    cout << o << endl;
    */

    // Rect
    Rect r1(a, b);
    r1.showInfo();
    cout << endl;
    /*
    r1.showInfo();
    cout << endl;
    cout << r1.isValid() << endl;
    cout << r1.contain(o) << endl;
    */

    /*
    Rect r2(b, a);
    r2.showInfo();
    cout << endl;
    cout << r2.isValid() << endl;

    Rect r3(a, a);
    r3.showInfo();
    cout << endl;
    cout << r3.isValid() << endl;

    Rect r4(Coord(2,3), Coord(5,5));
    r4.showInfo();
    cout << endl;
    cout << r4.isValid() << endl;
    */

    DoubleCircle c1;
    DoubleCircle c2(1, 2), c3(2, 4);
    /*
    c1.showInfo();
    cout << endl;
    cout << "Валиден: " << c1.isValid() << endl;
    c2.showInfo();
    cout << endl;
    cout << "Валиден: " << c2.isValid() << endl;
    c3.showInfo();
    cout << endl;
    cout << "Валиден: " << c3.isValid() << endl;
    cout << c3.getInnerRad() << ", " << c3.getOutterRad() << endl;
    cout << "c1 < c2: " << (c1 < c2) << ", c2 < c3: " << (c2 < c3) << ", c2 < c2: " << (c2 < c2);
    */

    Bolt bolt1;
    Bolt bolt2(c2), bolt3(c3);
    bolt2.showInfo();

    /*
    bolt2.showInfo();
    cout << bolt2.isValid() << endl;

    cout << "b1 < b2: " << (bolt1 < bolt2) << ", bolt2 < bolt3: " << (bolt2 < bolt3) <<
        ", bolt3 < bolt2: " << (bolt3 < bolt2) << "b1 < b1: " << (bolt1 < bolt1) << endl;

    if (bolt2.setCenter(Coord(3, 3))) {
        cout << "Новый центр: " << bolt2.getCenter() << endl;
    }
    bolt2.resetCenter();
    if (bolt2.setCenter(Coord(2, 2))) {
        Coord center = bolt2.getCenter();
        cout << "Новый центр: " << center << endl;
    }
    */

    /*
    if (bolt2.setCenter(Coord(1, 1))) {
        cout << "Новый центр: " << bolt2.getCenter() << endl;
    }
    for (Coord c : bolt2.innerVertices) cout << c << endl;
    */

    /*
    cout << bolt2.calcPotencial() << endl;
    Rect b2rect = bolt2.turnIntoRect();
    b2rect.showInfo();
    */

    bolt2.setCenter(Coord(3, 3));
    cout << "Новый центр: " << bolt2.getCenter() << endl;
    for (Coord c : bolt2.innerVertices) cout << c << endl;
    cout << "Полностью внутри: " << bolt2.allInside(r1) << endl;
    cout << "Пересекает: " << bolt2.intersect(r1);




    return 0;
}