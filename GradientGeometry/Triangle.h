#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"
#include <functional>
#include <windows.h>
using namespace std;

class Triangle : public Figure
{
	Point A, B, C;
	double Square = NULL;
	static void VertexSort(Point& a, Point& b, Point& c);
	public:
	Triangle(int x1, int  y1, int x2, int y2, int x3, int y3);
	Triangle(Point a, Point b, Point c);
	static double GetSquare(int x0, int  y0, int x1, int y1, int x2, int y2);
	static double GetSquare(Point a, Point b, Point c);
	double GetSquare();
	void Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	void Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	COLORREF GetColor(int x, int y);
	COLORREF GetMagicColor(int x, int y);
	static COLORREF GetColor(Point& a, Point& b, Point& c, int x, int y);
};
