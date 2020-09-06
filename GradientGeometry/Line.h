#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"
#include <functional>
#include "Box.h"
#include <windows.h>

class Line: public Figure
{
	Point A, B;
	float Lenght = NULL;
	Box * DrawBox=NULL;
	Box * GetDrawBox();
	public:
	Line(int x0, int  y0, int x1, int y1);
	Line(Point a, Point b);
	~Line();
	static double GetLength(int x0, int  y0, int x1, int y1);
	static double GetLength(Point a, Point b);
	double GetLength();
	void Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	void Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	COLORREF GetColor(int x, int y);
	COLORREF GetMagicColor(int x, int y);
};

