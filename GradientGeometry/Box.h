#pragma once
#include "Figure.h"
#include "Point.h"
#include "Canvas.h"
#include <functional>
#include <windows.h>

using namespace std;
class Box: public Figure
{
	Point A, B;
	int Square = NULL;
	int Width = NULL;
	int Height = NULL;

	public:
	Box(int x0, int  y0, int x1, int y1); 
	Box(Point A_, Point B_);
	static int GetWidth(Point& a, Point& b);
	static int GetHeight(Point& a, Point& b);
	static int GetWidth(int& x0, int& y0, int& x1, int& y1);
	static int GetHeight(int& x0, int& y0, int& x1, int& y1);
	int GetWidth();
	int GetHeight();
	static int GetSquare(Point& A_, Point& B_);
	static int GetSquare(int& x0, int& y0, int& x1, int& y1);
	int GetSquare();
	void Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	void Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor);
	COLORREF GetColor(int x, int y);
	static 	COLORREF GetColor(Point A, Point B, int x, int y);
	static 	COLORREF GetColor(int x0, int y0, int x1, int y1, int x, int y);
};

