#include "Line.h"

	Line::Line(int x0, int  y0, int x1, int y1):A(x0, y0), B(x1, y1)
	{

	}

	Line::Line(Point a, Point b) : A(a), B(b)
	{

	}
	Line::~Line()
	{
		if (DrawBox != NULL)
			delete DrawBox;
	}
	Box* Line::GetDrawBox()
	{
		double _025 = GetLength() * 0.25;
		DrawBox = DrawBox == NULL ? new Box(0,0, _025, _025) : DrawBox;
		return DrawBox;
	}
	double Line::GetLength(int x0, int  y0, int x1, int y1)
	{
		return sqrt(pow(x1 - x0,2.0) + pow(y1 - y0, 2.0));
	}

	double Line::GetLength(Point a, Point b)
	{
		return Line::GetLength(a.X, a.Y, b.X, b.Y);
	}

	double Line::GetLength()
	{
		Lenght = Lenght == NULL ? Line::GetLength(A, B) : Lenght;
		return Lenght;
	}

	void Line::Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		if (A.Y > B.Y)
			swap(A, B);
		Point A0 = A;
		int deltaX = abs(B.X - A.X);
		int deltaY = abs(B.Y - A.Y);
		int signX = A.X < B.X ? 1 : -1;
		int signY = A.Y < B.Y ? 1 : -1;
		int error = deltaX - deltaY;
		bool exit = false;
		while (!exit)
		{
			canvas.DrawPixel(A0.X, A0.Y, getColor(A0.X, A0.Y));
			if (A0.Y < B.Y)
			{
				if (2 * error < deltaX)
				{
					error += deltaX;
					A0.Y += signY;
				}

				if (2 * error > -deltaY)
				{
					error -= deltaY;
					A0.X += signX;
				}
			}
			else
				exit = true;
		}
	}

	void Line::Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		Draw(canvas, getColor);
	}

	COLORREF Line::GetColor(int x, int y)
	{
		x -= A.X;
		double currentLenght = Line::GetLength(A.X, A.Y, x, y);

		int _025 = Line::GetLength() * 0.25;
		int _05 = _025 *2;
		int _075 = _025*3;

		if (currentLenght <= _025)
		{
			return GetDrawBox()->GetColor(_025 - currentLenght, _025);
		}
		else if (currentLenght <= _05)
		{
			currentLenght -= _025;
			return GetDrawBox()->GetColor(0, _025- currentLenght);
		}
		else if (currentLenght <= _075)
		{
			currentLenght -= _05;
			return GetDrawBox()->GetColor(currentLenght, 0);
		}
		currentLenght -= _075;

		return GetDrawBox()->GetColor(_025, currentLenght);
	}
	
//Othet altgorihtm

//bool draw()
//{
//	int deltax = abs(B.X - A.X);
//	int deltay = abs(B.Y - A.Y);
//	int error = 0;
//	bool flag = (deltax >= deltay);
//	if (((A.X > B.X) && (flag)) || ((A.Y > B.Y) && (!flag)))
//		swap(A, B);
//	int dir = flag ? ((B.Y - A.Y) > 0 ? 1 : -1) : ((B.X - A.X) > 0 ? 1 : -1);
//	int delta = flag ? deltax : deltay;
//	int deltaerr = flag ? deltay : deltax;
//	int b = flag ? A.Y : A.X;
//	int a_max = flag ? max(B.X, A.X) : max(B.Y, A.Y);
//	int b_max = flag ? max(B.Y, A.Y) : max(B.X, A.X);;
//	int a_min = flag ? min(B.X, A.X) : min(B.Y, A.Y);
//	int b_min = flag ? min(B.Y, A.Y) : min(B.X, A.X);
//	for (int a = a_min; a <= a_max; a++)
//	{
//		if (flag)
//			Canvas->draw_pixel(a, b);
//		else
//			Canvas->draw_pixel(b, a);
//		error += deltaerr;
//		if (2 * error >= delta)
//		{
//			b += dir;
//			error -= delta;
//		}
//	}
//	return true;
//}