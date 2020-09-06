#pragma once

#include <windows.h>
#include "Figure.h"

class Canvas
{
	HWND console;
	HDC dc;
	RECT window;
	void GetScreen();
	public:
	Canvas();
	void DrawPixel(int x, int y, COLORREF color);
	void DrawFigure(Figure& figure, COLORREF color=NULL);
	void FillFigure(Figure& figure, COLORREF color=NULL);
};
