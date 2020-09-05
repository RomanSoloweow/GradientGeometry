#include "Box.h"

	Box::Box(int x0, int  y0, int x1, int y1) :A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1))
	{

	}

	Box::Box(Point A_, Point B_) :A(min(A_.X, B_.X), min(A_.Y, B_.Y)), B(max(A_.X, B_.X), max(A_.Y, B_.Y))
	{

	}
	int Box::GetWidth(Point& a, Point& b)
	{
		return Box::GetWidth(a.X, a.Y, b.X, b.Y);
	}

	int Box::GetHeight(Point& a, Point& b)
	{
		return Box::GetHeight(a.X, a.Y, b.X, b.Y);
	}

	int Box::GetWidth(int& x0, int& y0, int& x1, int& y1)
	{
		return max(y0, y1) - min(y0, y1);
	}
	int Box::GetHeight(int& x0, int& y0, int& x1, int& y1)
	{
		return max(x0, x1) - min(x0, x1);
	}

	int Box::GetWidth()
	{
		return Box::GetWidth(A, B);
	}

	int Box::GetHeight()
	{
		return Box::GetHeight(A, B);
	}
	int Box::Square(Point& a, Point& b)
	{
		return Box::Square(a.X, a.Y, b.X, b.Y);
	}

	int Box::Square(int& x0, int& y0, int& x1, int& y1)
	{
		return ((max(x0, x1) - min(x0, x1)) * (max(y0, y1) - min(y0, y1)));
	}

	int Box::Square()
	{
		return Box::Square(A, B);
	}

	void Box::Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		for (int i = A.X; i <= B.X; i++)
		{
			canvas.DrawPixel(i, A.Y, getColor(i, A.Y));
			canvas.DrawPixel(i, B.Y, getColor(i, B.Y));
		}
		for (int i = A.Y; i <= B.Y; i++)
		{
			canvas.DrawPixel(A.X, i, getColor(A.X, i));
			canvas.DrawPixel(B.X, i, getColor(B.X, i));
		}
	}

	void Box::Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		for (int i = A.Y; i <= B.Y; i++)
			for (int j = A.X; j <= B.X; j++)
				canvas.DrawPixel(j, i, getColor(i,j));
	}

	COLORREF Box::GetColor(int x, int y)
	{
		return RGB(0, 0, 0);
	}