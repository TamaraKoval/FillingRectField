#include <iostream>
#include "Geometry.h"
#include "Objects.h"
#include "FieldBuilder.h"
#include "FieldPainter.h"
#include "FieldParser.h"

int main() {
    setlocale(LC_ALL, "Russian");

    FieldBuilder builder;
    FieldParser parser;

    if (parser.getDataFromXML(builder)) {
        if (builder.build()) {
            std::cout << "Сборка удалась" << std::endl;
            FieldPainter painter(builder);
            if (painter.draw()) std::cout << "Файл bmp сгенерирован";
            parser.putDataToXML(builder.getInstalledBolts());
        }
        else {
            std::cout << "Ошибка при генерации чертежа" << std::endl;
        }
    } else {
        std::cout << "Не удалось считать файл";
    }

    return 0;
}