#include "FieldPainter.h"

FieldPainter::FieldPainter(const FieldBuilder& builder) {
	baseField = builder.getbasefield();
	obstructions = builder.getObstructions();
	bolts = builder.getInstalledBolts();

	side = abs(baseField.getTop());
	if (abs(baseField.getRight()) > side) side = abs(baseField.getRight());
	if (abs(baseField.getLeft()) > side) side = abs(baseField.getLeft());
	if (abs(baseField.getBottom()) > side) side = abs(baseField.getBottom());
	side  = (side + 50) * 4;
}

Coord FieldPainter::convert(const Coord& coord) {
	double x = coord.getX() * 2;
	double y = coord.getY() * 2;
	return { side / 2 + x, side / 2 + y };
}

void FieldPainter::printRect(const Mat& image, const RectByCoords& rect, Scalar colour, int thickness) {
	Point endRect(convert(rect.getMinPoint()).getX(), convert(rect.getMinPoint()).getY());
	Point startRect(convert(rect.getMaxPoint()).getX(), convert(rect.getMaxPoint()).getY());
	rectangle(image, endRect, startRect, colour, thickness);
}

void FieldPainter::printCircle(const Mat& image, const Coord& center, int rad, Scalar colour, int thickness) {
	Point pCenter(convert(center).getX(), convert(center).getY());
	circle(image, pCenter, rad, colour, thickness);
}

void FieldPainter::draw() {
	
	Mat image(side, side, CV_8UC3, Scalar(255, 255, 255));

	line(image, Point(0, side / 2), Point(side, side / 2), axisColour, 1);
	line(image, Point(side / 2, 0), Point(side / 2, side), axisColour, 1);

	printRect(image, baseField, borderColour, 2);

	for (Obstruction& obs : obstructions) {
		printRect(image, obs.getBorders(), rectColour, -1);
	}

	for (Bolt& b : bolts) {
		printCircle(image, b.getCenter(), b.getInnerRad(), littleCircleColour, 1);
		printCircle(image, b.getCenter(), b.getOutterRad(), bigCircleColour, 2);
	}

	Mat flipped;
	flip(image, flipped, 0);

	imwrite("circletest.bmp", flipped);
}
