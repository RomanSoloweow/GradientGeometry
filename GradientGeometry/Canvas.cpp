#include "Canvas.h"
#include <windows.h>
#include "Point.h"
#include "Figure.h"
#include <functional>

using namespace std;
using namespace placeholders;
	bool Canvas::PointInside(int a, int b)
	{
		if ((a > B.X) || (a < A.X))
			return false;
		if ((b > B.Y) || (b < A.Y))
			return false;
		return true;
	}

	void Canvas::GetScreen()
	{
		console = GetConsoleWindow();
		dc = GetDC(console);
		GetWindowRect(console, &window);
	}

	COLORREF Canvas::GetColor(int x, int y)
	{
		if (DefaultColor != NULL)
			return *DefaultColor;

		double r_ = 0, g_ = 0, b_ = 0;
		if (PointInside(x, y))
		{
			r_ = 255.000 * (y - A.Y) / GetHeight();
			b_ = 255.000 * (x - A.X) / GetWidth();
			g_ = 255.000 - ((r_ + b_) / 2);
		}
		else
		{
			r_ = 255, g_ = 255, b_ = 255;
		}
		COLORREF color = RGB(r_, g_, b_);
		return color;
	}

	Canvas::Canvas(int x0, int y0, int x1, int y1, COLORREF color): A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1))
	{
		if (color != NULL)
			DefaultColor = new COLORREF(color);

		GetScreen();
	}

	Canvas::Canvas(Point& a, Point& b, COLORREF color) :Canvas(a.X, a.Y, b.X, b.Y, color)
	{
		
	}
	int Canvas::GetWidth()
	{
		return (B.X - A.X);
	}

	int Canvas::GetHeight()
	{
		return (B.Y - A.Y);
	}
	
	void Canvas::DrawPixel(int x, int y)
	{
		SetPixel(this->dc, x, y, this->GetColor(x, y));
	}

	void Canvas::DrawPixel(int x, int y, COLORREF color)
	{
		SetPixel(this->dc, x, y, color);
	}

	void Canvas::DrawFigure(Figure& figure, bool newGradient)
	{
		/*if (newGradient)
		{
			figure.Draw(*this, bind(&Figure::GetColor, figure, _1, _2));
		}
		else
		{*/
			figure.Draw(*this, bind(&Canvas::GetColor, this, _1, _2));
		/*}*/
	}

	void Canvas::FillFigure(Figure& figure, bool newGradient)
	{
		if (newGradient)
		{
			figure.Fill(*this, bind(&Figure::GetColor, figure, _1, _2));
		}
		else
		{
			figure.Fill(*this, bind(&Canvas::GetColor, this, _1, _2));
		}
	}

