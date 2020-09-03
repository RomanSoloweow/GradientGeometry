#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"

class Box: public Figure
{
	Point A, B;

	public:

	Box(int x0, int  y0, int x1, int y1);
	Box(Point A_, Point B_);
	static int GetWidth(Point& a, Point& b);
	static int GetHeight(Point& a, Point& b);
	static int GetWidth(int& x0, int& y0, int& x1, int& y1);
	static int GetHeight(int& x0, int& y0, int& x1, int& y1);
	int GetWidth();
	int GetHeight();
	static int Square(Point& A_, Point& B_);
	static int Square(int& x0, int& y0, int& x1, int& y1);
	int Square();
	void Draw(Canvas& canvas, bool asNewCanvas = true);
	void Fill(Canvas& canvas, bool asNewCanvas = true);

};

