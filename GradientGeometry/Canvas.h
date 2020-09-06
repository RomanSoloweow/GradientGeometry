#pragma once

#include "Point.h"
#include <windows.h>

#include "Figure.h"
#include <functional>

class Canvas
{
	HWND console;
	HDC dc;
	RECT window;
	Point A, B;
	bool PointInside(int a, int b);
	void GetScreen();

	public:
	COLORREF GetColor(int x, int y);
	Canvas(int x0, int y0, int x1, int y1);
	Canvas(Point& a, Point& b);
	int GetWidth();
	int GetHeight();
	void DrawPixel(int x, int y);
	void DrawPixel(int x, int y, COLORREF color);
	void DrawFigure(Figure& figure, bool newGradient = true);
	void FillFigure(Figure& figure, bool newGradient = true);

	void DrawFigureMagicColor(Figure& figure);
	void FillFigureMagicColor(Figure& figure);
};
