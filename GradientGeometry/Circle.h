#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"
#include <functional>
#include <windows.h>

class Circle: public Figure
{
	Point O;
	int R;
	double Square = NULL;
	public:
	Circle(int x, int y, int r);
	Circle(Point o, int r);
	static double GetSquare(int& r);
	double GetSquare();
	void Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	void Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	COLORREF GetColor(int x, int y);
	static COLORREF GetColor(Point o, int radius, int x, int y);
};
