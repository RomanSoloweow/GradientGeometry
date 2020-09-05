#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"
#include <functional>
#include <windows.h>

class Circle: public Figure
{
	Point O;
	int Radius;
	public:
	Circle(int x, int y, int radius);
	Circle(Point o, int radius);
	static float Square(int& radius);
	float Square();
	void Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	void Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	COLORREF GetColor(int x, int y);
};
