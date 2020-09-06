#include "Box.h"

	Box::Box(int x0, int  y0, int x1, int y1) :A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1))
	{
	
	}

	Box::Box(Point A_, Point B_):A(min(A_.X, B_.X), min(A_.Y, B_.Y)), B(max(A_.X, B_.X), max(A_.Y, B_.Y))
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
		Width = Width == NULL ? Box::GetWidth(A, B) : Width;
		return Width;
	}

	int Box::GetHeight()
	{
		Height = Height == NULL ? Box::GetHeight(A, B) : Height;
		return Height;
	}
	int Box::GetSquare(Point& a, Point& b)
	{
		return Box::GetSquare(a.X, a.Y, b.X, b.Y);
	}

	int Box::GetSquare(int& x0, int& y0, int& x1, int& y1)
	{
		return ((max(x0, x1) - min(x0, x1)) * (max(y0, y1) - min(y0, y1)));
	}

	int Box::GetSquare()
	{
		Square = Square == NULL ? Box::GetSquare(A, B) : Square;
		return Square;
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
				canvas.DrawPixel(j, i, getColor(j, i));
	}

	COLORREF Box::GetColor(int x, int y)
	{
		double r_ = 0, g_ = 0, b_ = 0;
		r_ = 255.000 * (x - A.X) / GetHeight();
		b_ = 255.000 * (y - A.Y) / GetWidth();
		g_ = 255.000 - ((r_ + b_) / 2);
		return RGB(r_, g_, b_);
	}
	COLORREF Box::GetColor(Point A_, Point B_, int x, int y)
	{
		return Box::GetColor(A_.X, A_.Y, B_.X, B_.Y, x, y);
	}
	COLORREF Box::GetColor(int x0, int y0, int x1, int y1, int x, int y)
	{
		double r_ = 0, g_ = 0, b_ = 0;
		r_ = 255.000 * (x - x0) / Box::GetHeight(x0,y0,x1,y1); 
		b_ = 255.000 * (y - y0) / Box::GetWidth(x0, y0, x1, y1);
		g_ = 255.000 - ((r_ + b_) / 2);
		return RGB(r_, g_, b_);
	}
	//unique color
	//COLORREF Box::GetColor(int x, int y)
	//{
	//	double r_ = 0, g_ = 0, b_ = 0;
	//	auto height = GetHeight() / 2;
	//	auto widht = GetWidth() / 2;
	//	r_ = 255.000 * (y - A.Y) /2 * height;
	//	b_ = 255.000 * (x - A.X) / 2 * widht;
	//	g_ = 255.000 - ((r_ + b_) / 2);
	//	return RGB(r_, g_, b_);
	//}