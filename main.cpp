#include <iostream>
#include "Geometry.h"
#include "Objects.h"
#include "FieldBuilder.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Rect field(Coord(-50, -100), Coord(50, 100));

    Obstruction obs1(Rect(Coord(-5, -100), Coord(5, 100)));
    Obstruction obs2(Rect(Coord(-50, -100), Coord(-30, -80)));

    Bolt b1(DoubleCircle(12, 20));
    Bolt b2(DoubleCircle(25, 30));
    Bolt b3(DoubleCircle(32, 35));
    Bolt b4(DoubleCircle(25, 30));
    Bolt b5(DoubleCircle(12, 20));

    FieldBuilder builder(field);
    builder.setObstruction(obs1);
    builder.setObstruction(obs2);
    builder.addBolt(b1);
    builder.addBolt(b2);
    builder.addBolt(b3);
    builder.addBolt(b4);
    builder.addBolt(b5);

    if (builder.build()) {
        std::cout << "Сборка удалась" << std::endl;
        vector<Bolt> bolts = builder.getInstalledBolts();
        for (Bolt b : bolts) b.showInfo();
    }
    else {
        std::cout << "Что-то пошло не так" << std::endl;
    }

    return 0;
}