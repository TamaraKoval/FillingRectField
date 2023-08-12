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
	Color rectColor = Color(255, 185, 184, 255);
	Color bigCircleColor = Color(255, 255, 107, 73);
	Color littleCircleColor = Color(255, 255, 226, 187);
	Color axisColor = Color(255, 255, 239, 188);
	void printRect(Graphics& graphics, Pen& pen, const RectByCoords& rect);
public:
	FieldPainter() = default;
	explicit FieldPainter(const FieldBuilder& builder);
	bool draw();
};