#pragma once
#include <windows.h>
#include <functional>

class Canvas;
using namespace std;
class Figure
{
	public:
	virtual void Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor) = 0;
	virtual void Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor) = 0;
	virtual COLORREF GetColor(int x, int y) = 0;
};

