#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <gdiplusimaging.h>
#include "FieldBuilder.h"
#include "Objects.h"
#pragma comment (lib,"gdiplus.lib")

using namespace Gdiplus;

class FieldPainter {
	int side = 500;
	RectByCoords baseField;
	vector<Obstruction> obstructions;
	vector<Bolt> bolts;
	Color borderColor = Color(255, 0, 0, 0);
	Color obsOutColor = Color(255, 255, 0, 0);
	Color obsInColor = Color(64, 255, 0, 0);
	Color bigCircleColor = Color(255, 73, 107, 255);
	Color littleCircleColor = Color(255, 187, 226, 255);
	Color axisColor = Color(255, 255, 239, 188);
	void printRect(Graphics& graphics, Pen* pen, SolidBrush* brush, const RectByCoords& rect);
	void printDoubleCircle(Graphics& graphics, Pen& penForInnerCircle, Pen& penForOutterCircle, const Bolt& bolt);
public:
	FieldPainter() = default;
	explicit FieldPainter(const FieldBuilder& builder);
	bool draw();
};