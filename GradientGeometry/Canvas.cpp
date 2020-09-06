#include "Canvas.h"
#include <windows.h>
#include "Figure.h"
#include <functional>

using namespace std;
using namespace placeholders;


	void Canvas::GetScreen()
	{
		console = GetConsoleWindow();
		dc = GetDC(console);
		GetWindowRect(console, &window);
	}

	Canvas::Canvas()
	{
		GetScreen();
	}

	void Canvas::DrawPixel(int x, int y, COLORREF color)
	{
		SetPixel(this->dc, x, y, color);
	}

	void Canvas::DrawFigure(Figure& figure, COLORREF color)
	{
		if(color == NULL)
			figure.Draw(*this, bind(&Figure::GetColor, &figure, _1, _2));
		else
			figure.Draw(*this, [=](int x, int y) { return color; });
	}

	void Canvas::FillFigure(Figure& figure, COLORREF color)
	{
 		if (color == NULL)
			figure.Fill(*this, bind(&Figure::GetColor, &figure, _1, _2));
		else
			figure.Fill(*this, [=](int x, int y) { return color; });
	}

