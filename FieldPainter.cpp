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
		if (pImageCodecInfo[j].MimeType != nullptr && wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1; 
}

void FieldPainter::printRect(Graphics& graphics, Pen& pen, const RectByCoords& rect) {
	int width = rect.getWidth() * 2;
	int height = rect.getHeight() * 2;

	int newX = (side / 2) + rect.getMinPoint().getX() * 2;
	int newY = (side / 2) - rect.getMaxPoint().getY() * 2;

	graphics.DrawRectangle(&pen, newX, newY, width, height);
}

bool FieldPainter::draw() {

	GdiplusStartupInput gdiplusStartupInput;
	gdiplusStartupInput.GdiplusVersion = 1;
	ULONG_PTR gdiplusToken;
	Status status = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	if (status != Status::Ok) {
		return false;
	}

	Bitmap bmp(side, side, PixelFormat32bppARGB);
	Graphics graphics(&bmp);
	graphics.Clear(Color::White);

	Pen pen(axisColor);
	graphics.DrawLine(&pen, 0, side / 2, side, side / 2);
	graphics.DrawLine(&pen, side / 2, 0, side / 2, side);

	pen.SetColor(borderColor);
	pen.SetWidth(2);
	printRect(graphics, pen, baseField);

	Bitmap convertedBmp(side, side, PixelFormat24bppRGB);
	Graphics convGraphics(&convertedBmp);
	convGraphics.DrawImage(&bmp, 0, 0, side, side);

	CLSID encoderClsid;
	GetEncoderClsid(L"image/bmp", &encoderClsid);
	convertedBmp.Save(L"image.bmp", &encoderClsid);

	GdiplusShutdown(gdiplusToken);

	return true;

}
