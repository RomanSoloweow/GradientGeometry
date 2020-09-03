#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"


class Circle: public Figure
{
	Point O;
	int Radius;
	public:
	Circle(int x, int y, int radius);
	Circle(Point o, int radius);
	static float Square(int& radius);
	float Square();
	void Draw(Canvas& canvas, bool asNewCanvas = true);
	void Fill(Canvas& canvas, bool asNewCanvas = true);
};
