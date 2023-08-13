#include "FieldPainter.h"

using namespace Gdiplus;

FieldPainter::FieldPainter(const FieldBuilder& builder) {
	baseField = builder.getbasefield();
	obstructions = builder.getObstructions();
	bolts = builder.getInstalledBolts();

	side = abs(baseField.getTop());
	if (abs(baseField.getRight()) > side) side = abs(baseField.getRight());
	if (abs(baseField.getLeft()) > side) side = abs(baseField.getLeft());
	if (abs(baseField.getBottom()) > side) side = abs(baseField.getBottom());
	side = (side + 50) * 4;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
	UINT num = 0;
	UINT size = 0;

	ImageCodecInfo* pImageCodecInfo = nullptr;

	GetImageEncodersSize(&num, &size);
	if (size == 0) {
		return -1;
	}

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == nullptr) {
		return -1;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j) {
		if (pImageCodecInfo[j].MimeType != nullptr && format != nullptr && wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1; 
}

void FieldPainter::printRect(Graphics& graphics, Pen* pen, SolidBrush* brush, const RectByCoords& rect) {
	int width = rect.getWidth() * 2;
	int height = rect.getHeight() * 2;

	int newX = (side / 2) + rect.getMinPoint().getX() * 2;
	int newY = (side / 2) - rect.getMaxPoint().getY() * 2;

	if (pen != nullptr) {
		graphics.DrawRectangle(pen, newX, newY, width, height);
	}

	if (brush != nullptr) {
		graphics.FillRectangle(brush, newX, newY, width, height);
	}
}

void FieldPainter::printDoubleCircle(Graphics& graphics, Pen& penForInnerCircle, Pen& penForOutterCircle, const Bolt& bolt) {
	int innerR = bolt.getInnerRad() * 2;
	int outterR = bolt.getOutterRad() * 2;

	int centerX = (side / 2) + bolt.getCenter().getX() * 2;
	int centerY = (side / 2) - bolt.getCenter().getY() * 2;

	graphics.DrawEllipse(&penForInnerCircle, centerX - innerR / 2, centerY - innerR / 2, innerR, innerR);
	graphics.DrawEllipse(&penForOutterCircle, centerX - outterR / 2, centerY - outterR / 2, outterR, outterR);
}

bool FieldPainter::draw() {

	GdiplusStartupInput gdiplusStartupInput;
	gdiplusStartupInput.GdiplusVersion = 1;
	ULONG_PTR gdiplusToken;
	Status status = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	if (status != Status::Ok) {
		return false;
	}

	Bitmap bmp(side, side, PixelFormat24bppRGB);
	Graphics graphics(&bmp);
	graphics.Clear(Color::White);

	Pen pen(axisColor);
	graphics.DrawLine(&pen, 0, side / 2, side, side / 2);
	graphics.DrawLine(&pen, side / 2, 0, side / 2, side);

	pen.SetColor(borderColor);
	pen.SetWidth(2);
	printRect(graphics, &pen, nullptr, baseField);

	pen.SetColor(obsOutColor);
	pen.SetWidth(1);
	SolidBrush brush(obsInColor);
	for (Obstruction& obs : obstructions) {
		printRect(graphics, &pen, &brush, obs.getBorders());
	}

	Pen pen2(bigCircleColor, 2);
	pen.SetColor(littleCircleColor);
	for (Bolt& b : bolts) {
		printDoubleCircle(graphics, pen, pen2, b);
	}

	CLSID encoderClsid;
	GetEncoderClsid(L"image/bmp", &encoderClsid);
	status = bmp.Save(L"image.bmp", &encoderClsid);
	if (status != Status::Ok) {
		GdiplusShutdown(gdiplusToken);
		return false;
	}

	GdiplusShutdown(gdiplusToken);

	return true;

}
