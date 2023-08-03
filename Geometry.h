#pragma once
#include <ostream>
#include <iostream>

class Coord {
	int x, y;
public:
	Coord() { x = 0; y = 0; }
	Coord(int xx, int yy) : x(xx), y(yy) {}
	void SetCoord(int xx, int yy) { x = xx; y = yy; }
	void SetX(int xx) { x = xx; }
	void SetY(int yy) { y = yy; }
	int getX() { return x; }
	int getY() { return y; }
	Coord& operator=(Coord c);
	Coord operator+(Coord c);
	Coord operator-(Coord c);
	friend std::ostream& operator<<(std::ostream& stream, Coord& coords);
};

class Figure {
public:
	virtual bool isValid()  = 0;
};

class Rect : public Figure {
	Coord minPoint, maxPoint;
public:
	Rect() {}
	Rect(Coord min, Coord max) : minPoint(min), maxPoint(max) {}
	Coord getMinPoint() { return minPoint; }
	Coord getMaxPoint() { return maxPoint; }
	int getTop() { return maxPoint.getY(); }
	int getLeft() { return maxPoint.getX(); }
	int getBottom() { return minPoint.getY(); }
	int getRight() { return minPoint.getY(); }
	Rect& operator=(Rect r); // протестировать
	void showInfo() { std::cout << "Ќижний угол: " << minPoint << ", верхний угол: " << maxPoint; } // на удаление (+инклуд)
	bool isValid() override;
	bool contain(Coord coord);
};

class DoubleCircle : public Figure {
	int innerRad, outterRad;
public:
	DoubleCircle() : innerRad(0), outterRad(0) {}
	DoubleCircle(int innerR, int outterR) : innerRad(innerR), outterRad(outterR) {}
	void showInfo() { std::cout << "¬нутренний r: " << innerRad << ", внешний r: " << outterRad; } // на удаление (+инклуд)
	int getInnerRad() { return innerRad; }
	int getOutterRad() { return outterRad; }
	bool isValid() override;
	bool operator<(DoubleCircle dc);
};

