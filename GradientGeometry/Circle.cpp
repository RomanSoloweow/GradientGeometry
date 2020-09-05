#include "Circle.h"

	Circle::Circle(int x, int y, int radius) :O(x, y), Radius(radius)
	{

	}

	Circle::Circle(Point o, int radius) : O(o), Radius(radius)
	{

	}

	float Circle::Square(int& radius)
	{
		return 3.14159265358979323846 * radius * radius;
	}

	float  Circle::Square()
	{
		return Circle::Square(Radius);
	}

	void  Circle::Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		int x = 0;
		int y = Radius;
		int delta = 1 - 2 * Radius;
		int error = 0;
		while (y >= 0)
		{
			canvas.DrawPixel(O.X + x, O.Y + y, getColor(O.X + x, O.Y + y));
			canvas.DrawPixel(O.X + x, O.Y - y, getColor(O.X + x, O.Y - y));
			canvas.DrawPixel(O.X - x, O.Y + y, getColor(O.X - x, O.Y + y));
			canvas.DrawPixel(O.X - x, O.Y - y, getColor(O.X - x, O.Y - y));
			error = 2 * (delta + y) - 1;
			if (delta < 0 && error <= 0)
			{
				++x;
				delta += 2 * x + 1;
				continue;
			}
			error = 2 * (delta - x) - 1;
			if (delta > 0 && error > 0)
			{
				--y;
				delta += 1 - 2 * y;
				continue;
			}
			if (x < Radius)
				++x;
			delta += 2 * (x - y);
			--y;
		}
	}
	
	void  Circle::Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		int x = 0;
		int y = Radius;
		int delta = 1 - 2 * Radius;
		int error = 0;
		while (y >= 0)
		{
			for (int i = O.X - x; i <= O.X + x; i++)
				canvas.DrawPixel(i, O.Y + y, getColor(i, O.Y + y));
			for (int i = O.X - x; i <= O.X + x; i++)
				canvas.DrawPixel(i, O.Y - y, getColor(i, O.Y - y));
			error = 2 * (delta + y) - 1;
			if (delta < 0 && error <= 0)
			{
				++x;
				delta += 2 * x + 1;
				continue;
			}
			error = 2 * (delta - x) - 1;
			if (delta > 0 && error > 0)
			{
				--y;
				delta += 1 - 2 * y;
				continue;
			}
			if (x < Radius)
				++x;
			delta += 2 * (x - y);
			--y;
		}
	}

	COLORREF Circle::GetColor(int x, int y)
	{
		return RGB(0, 0, 0);
	}