#pragma once
#include <opencv2/opencv.hpp>
#include "FieldBuilder.h"
#include "Objects.h"

using namespace cv;

class FieldPainter {
    int side = 500;
    RectByCoords baseField;
    vector<Obstruction> obstructions;
    vector<Bolt> bolts;
    Scalar borderColour = Scalar(0, 0, 0);
    Scalar rectColour = Scalar(185, 184, 255);
    Scalar bigCircleColour = Scalar(255, 107, 73);
    Scalar littleCircleColour = Scalar(255, 226, 187);
    Scalar axisColour = Scalar(188, 239, 255);
    Coord convert(const Coord& coord);
    void printRect(const Mat& image, const RectByCoords& rect, Scalar colour, int thickness);
    void printCircle(const Mat& image, const Coord& center, int rad, Scalar colour, int thickness);
public:
    FieldPainter() = default;
    explicit FieldPainter(const FieldBuilder& builder);
    bool draw();
};