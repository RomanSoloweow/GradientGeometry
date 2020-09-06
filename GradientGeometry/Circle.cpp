#include "Circle.h"

	Circle::Circle(int x, int y, int r) :O(x, y), R(r)
	{

	}

	Circle::Circle(Point o, int r) : O(o), R(r)
	{

	}

	double Circle::GetSquare(int& r)
	{
		return 3.14159265358979323846 * r * r;
	}

	double  Circle::GetSquare()
	{
		Square = Square == NULL ? Circle::GetSquare(R) : Square;
		return Square;
	}

	void  Circle::Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		int x = 0;
		int y = R;
		int delta = 1 - 2 * R;
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
			if (x < R)
				++x;
			delta += 2 * (x - y);
			--y;
		}
	}
	
	void  Circle::Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		int x = 0;
		int y = R;
		int delta = 1 - 2 * R;
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
			if (x < R)
				++x;
			delta += 2 * (x - y);
			--y;
		}
	}
	COLORREF Circle::GetColor(Point o, int r, int x, int y)
	{
		double r_ = 0, g_ = 0, b_ = 0;
		r_ = 255.000 * (y - (o.Y - r)) / (2 * r);
		b_ = 255.000 * (x - (o.X - r)) / (2 * r);
		g_ = 255.000 - ((r_ + b_) / 2);
		return RGB(r_, g_, b_);
	}

	COLORREF Circle::GetColor(int x, int y)
	{		
		return Circle::GetColor(O, R, x, y);
	}

	COLORREF Circle::GetMagicColor(int x, int y)
	{
		double r_ = 0, g_ = 0, b_ = 0;
		r_ = 255.000 * (y - (O.Y - R)) /2*R;
		b_ = 255.000 * (x - (O.X - R)) /2*R;
		g_ = 255.000 - ((r_ + b_) / 2);
		return RGB(r_, g_, b_);
	}