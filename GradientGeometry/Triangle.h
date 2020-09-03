#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"

class Triangle : public Figure
{
	Point A, B, C;
	void VertexSort(Point& a, Point& b, Point& c);
	COLORREF GetColor(Canvas& canvas, bool gradient, int& x, int& y);
	public:
	Triangle(int x1, int  y1, int x2, int y2, int x3, int y3);
	Triangle(Point a, Point b, Point c);
	static double Square(int x0, int  y0, int x1, int y1, int x2, int y2);
	static double Square(Point a, Point b, Point c);
	double Square();
	void Draw(Canvas& canvas, bool asNewCanvas = true);
	void Fill(Canvas& canvas, bool asNewCanvas = true);
};
