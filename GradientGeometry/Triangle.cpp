#include "Triangle.h"
#include "Line.h"

	Triangle::Triangle(int x1, int  y1, int x2, int y2, int x3, int y3) :A(x1, y1), B(x2, y2), C(x3, y3)
	{
		VertexSort(A, B, C);
	}

	Triangle::Triangle(Point a, Point b, Point c) : A(a), B(b), C(c)
	{
		VertexSort(A, B, C);
	}

	void Triangle::VertexSort(Point& a, Point& b, Point& c)
	{
		if (b.Y < a.Y)
			swap(b, a);
		if (c.Y < a.Y)
			swap(c, a);
		if (c.Y < b.Y)
			swap(c, b);
	}

	double Triangle::Square(int x0, int  y0, int x1, int y1, int x2, int y2)
	{
		return (0.5 * abs((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)));
	}

	double Triangle::Square(Point a, Point b, Point c)
	{
		return Triangle::Square(a.X, a.Y, b.X, b.Y, c.X, c.Y);
	}

	double Triangle::Square()
	{
		return Triangle::Square(A, B, C);
	}

	void Triangle::Draw(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		Line Line1(A, B);
		Line Line2(A, C);
		Line Line3(B, C);

		Line1.Draw(canvas, getColor);
		Line2.Draw(canvas, getColor);
		Line3.Draw(canvas, getColor);
	}
			


	void Triangle::Fill(Canvas& canvas, function<COLORREF(int x, int y)> getColor)
	{
		Point P1 = A, P2 = A;
		int deltaX_1 = abs(B.X - A.X);
		int deltaY_1 = abs(B.Y - A.Y);
		int signX_1 = A.X < B.X ? 1 : -1;
		int signY_1 = A.Y < B.Y ? 1 : -1;
		int error_1 = deltaX_1 - deltaY_1;

		int deltaX_2 = abs(C.X - A.X);
		int deltaY_2 = abs(C.Y - A.Y);
		int signX_2 = A.X < C.X ? 1 : -1;
		int signY_2 = A.Y < C.Y ? 1 : -1;
		int error_2 = deltaX_2 - deltaY_2;
		bool exit_1 = false, exit_2 = false;

		float kof = 1.000 * deltaX_1 / deltaY_1;

		int left = (signX_2 != signY_2 ? 0 : signX_1), right = ((signX_1 != signY_1) ? 0 : 1);
		if (signX_1 <= signX_2)
			left = 1;
		while ((!exit_1) || (!exit_2))
		{
			if (P1.Y < B.Y)
			{

				if (2 * error_1 < deltaX_1)
				{
					error_1 += deltaX_1;
					P1.Y += signY_1;
				}
				if (2 * error_1 > -deltaY_1)
				{
					error_1 -= deltaY_1;
					P1.X += signX_1;
				}
			}
			else
				exit_1 = true;

			if (P2.Y < B.Y)
			{
				if (2 * error_2 < deltaX_2)
				{
					error_2 += deltaX_2;
					P2.Y += signY_2;
				}
				if (2 * error_2 > -deltaY_2)
				{
					error_2 -= deltaY_2;
					P2.X += signX_2;
				}
			}
			else
				exit_2 = true;

			for (int x = min(P1.X, P2.X) - kof * abs(P1.Y - P2.Y) * left; x <= max(P1.X, P2.X) + kof * abs(P1.Y - P2.Y) * right; x++)
				canvas.DrawPixel(x, P2.Y, getColor(x, P2.Y));

		}

		P1 = B;
		error_1 = 0;
		deltaX_1 = abs(C.X - B.X);
		deltaY_1 = abs(C.Y - B.Y);
		signX_1 = B.X < C.X ? 1 : -1;
		signY_1 = B.Y < C.Y ? 1 : -1;
		error_1 = deltaX_1 - deltaY_1;
		kof = 1.000 * deltaX_1 / deltaY_1;
		left = (signX_1 != signY_2 ? 0 : 1);
		right = (signY_1 == signX_2 ? 0 : 1);
		exit_1 = false;
		exit_2 = false;

		while ((!exit_1) || (!exit_2))
		{
			if (P1.Y < C.Y)
			{
				if (2 * error_1 < deltaX_1)
				{
					error_1 += deltaX_1;
					P1.Y += signY_1;
				}
				if (2 * error_1 > -deltaY_1)
				{
					error_1 -= deltaY_1;
					P1.X += signX_1;
				}
			}
			else
				exit_1 = true;
			if (P2.Y < C.Y)
			{
				if (2 * error_2 < deltaX_2)
				{
					error_2 += deltaX_2;
					P2.Y += signY_2;
				}
				if (2 * error_2 > -deltaY_2)
				{
					error_2 -= deltaY_2;
					P2.X += signX_2;
				}
			}
			else
				exit_2 = true;

			for (int x = min(P1.X, P2.X) + kof * abs(P1.Y - P2.Y) * left; x <= max(P1.X, P2.X) - kof * abs(P1.Y - P2.Y) * right; x++)
				canvas.DrawPixel(x, P2.Y, getColor(x, P2.Y));
		}
	}


	COLORREF Triangle::GetColor(int x, int y)
	{
		double r_ = 0, g_ = 0, b_ = 0;
		double square_ = Square();
		Point G(x, y), A_(A), B_(B), C_(C);
		r_ = 255.0 * Triangle::Square(G, A_, C_) / square_;
		b_ = 255.0 * Triangle::Square(G, B_, C_) / square_;
		g_ = 255.0 * Triangle::Square(G, A_, B_) / square_;
		COLORREF color = RGB(r_, g_, b_);
		return color;
	}

//	//перебираем точки
//	bool draw2()
//	{
//		int a, b, c;
//		for (int j = min(min(A.X, B.X), C.X); j < max(max(A.X, B.X), C.X); j++)
//			for (int i = min(min(A.Y, B.Y), C.Y); i < max(max(A.Y, B.Y), C.Y); i++)
//			{
//				a = (A.X - j) * (B.Y - A.Y) - (B.X - A.X) * (A.Y - i);
//				b = (B.X - j) * (C.Y - B.Y) - (C.X - B.X) * (B.Y - i);
//				c = (C.X - j) * (A.Y - C.Y) - (A.X - C.X) * (C.Y - i);
//				if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
//					Canvas->draw_pixel(j, i, get_color(j, i));
//			}
//		return true;
//	}
//	//вычисляем 
//	bool draw3()
//	{
//		float P1 = 0, P2 = 0;
//		float t = ((B.Y - A.Y) == 0 ? 1 : (B.Y - A.Y));
//		for (int y = A.Y; y < B.Y; y++)
//		{
//			P1 = A.X + (B.X - A.X) * (y - A.Y) / t;
//			P2 = A.X + (C.X - A.X) * (y - A.Y) / t;
//			for (int x = min(P1, P2); x <= max(P1, P2); x++)
//				Canvas->draw_pixel(x, y, get_color(x, y));
//		}
//		P1 = 0;
//		P2 = 0;
//		for (int y = B.Y; y < C.Y; y++)
//		{
//			P1 = B.X + (C.X - B.X) * (y - B.Y) / t;
//			P2 = A.X + (C.X - A.X) * (y - A.Y) / t;
//			for (int x = min(P1, P2); x <= max(P1, P2); x++)
//				Canvas->draw_pixel(x, y, get_color(x, y));
//		}
//		return true;
//	}
//};

//	void Rotate(float angle)
//	{
//		/*A.X = A.X * cos(alfa) - A.Y * sin(alfa);
//		A.Y = A.X * sin(alfa) + A.Y * cos(alfa);
//		B.X = B.X * cos(alfa) - B.Y * sin(alfa);
//		B.Y = B.X * sin(alfa) + B.Y * cos(alfa);
//		C.X = C.X * cos(alfa) - C.Y * sin(alfa);
//		C.Y = C.X * sin(alfa) + C.Y * cos(alfa);*/
//		float centerX = 195;
//		float  centerY = 195;
//		A.X = (A.X - centerX) * cos(angle) - (A.Y - centerY) * sin(angle) + centerX;
//		A.Y = (A.X - centerX) * sin(angle) + (A.Y - centerY) * cos(angle) + centerY;
//		B.X = (B.X - centerX) * cos(angle) - (B.Y - centerY) * sin(angle) + centerX;
//		B.Y = (B.X - centerX) * sin(angle) + (B.Y - centerY) * cos(angle) + centerY;
//		C.X = (C.X - centerX) * cos(angle) - (C.Y - centerY) * sin(angle) + centerX;
//		C.Y = (C.X - centerX) * sin(angle) + (C.Y - centerY) * cos(angle) + centerY;
//	}