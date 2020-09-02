#include <iostream> 
#include <windows.h>
#include <cmath>
using namespace std;
class point
{
public:
	int X, Y;
	point(int x, int y) :X(x), Y(y) {};
	point() :X(0), Y(0) { };
	friend ostream& operator<<(ostream& os, point& Point);
};
//вывод точки
ostream& operator<<(ostream& os, point& Point)
{
	os << "X: " << Point.X << "   Y: " << Point.Y;
	return os;
}
//обмен значениями 
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
//обмен значениями для точек
void swap(point& A, point& B)
{
	int temp = A.X;
	A.X = B.X;
	B.X = temp;
	temp = A.Y;
	A.Y = B.Y;
	B.Y = temp;
}
class canvas
{
	HWND console;
	HDC dc;
	RECT window = {};
	point A, B;
	COLORREF* default_color = NULL;
	//принадлежит ли точка области Канваса
	bool check_inside(int a, int b)
	{
		if ((a > B.X) || (a < A.X))
			return false;
		if ((b > B.Y) || (b < A.Y))
			return false;
		return true;
	}
	//получить управление консолью
	void screen()
	{
		console = GetConsoleWindow();
		dc = GetDC(console);
		GetWindowRect(console, &window);
	}
public:
	COLORREF get_color(int& x, int& y)
	{
		if (default_color != NULL)
			return *default_color;
		//cout << "x= " << x << "y= " << y << endl;
		double r_ = 0, g_ = 0, b_ = 0;
		if (check_inside(x, y))
		{
			r_ = 255.000 * (y - A.Y) / get_height();
			b_ = 255.000 * (x - A.X) / get_width();
			g_ = 255.000 - ((r_ + b_) / 2);
		}
		else
		{
			r_ = 255, g_ = 255, b_ = 255;
		}
		COLORREF color = RGB(r_, g_, b_);
		return color;
	}

	canvas(int x, int y, COLORREF colors) :A(10, 10), B(x, y), default_color(new COLORREF(colors))
	{
		screen();
	}
	canvas(int x0, int y0, int x1, int y1, COLORREF colors) :A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1)), default_color(new COLORREF(colors))
	{
		screen();
	}
	canvas(int x, int y) :A(10, 10), B(x, y)
	{
		screen();
	}
	canvas(int x0, int y0, int x1, int y1) :A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1))
	{
		screen();
	}
	canvas(point& A_, point& B_) :A(min(A_.X, B_.X), min(A_.Y, B_.Y)), B(max(A_.X, B_.X), max(A_.Y, B_.Y))
	{
		screen();
	}
	int get_width()
	{
		return (B.X - A.X);
	}
	int get_height()
	{
		return (B.Y - A.Y);
	}
	//закрасить пиксель (цвет определится по Конвасу)
	void draw_pixel(int x, int y)
	{
		SetPixel(this->dc, x, y, this->get_color(x, y));
	}
	//закрасить пиксель указанным цветом
	void draw_pixel(int x, int y, COLORREF color)
	{
		SetPixel(this->dc, x, y, color);
	}
};
class line
{
	point A, B;
	canvas* Canvas;
	//инициализация своего канваса, если он не был передан
	void initialization_canvas()
	{
		Canvas = new canvas(A, B);
	}
public:
	line(canvas& _Canvas, int x0, int  y0, int x1, int y1) :A(x0, y0), B(x1, y1)
	{
		Canvas = &_Canvas;
	}
	line(canvas& _Canvas, point A_, point B_) :A(A_), B(B_)
	{
		Canvas = &_Canvas;
	}
	line(int x0, int  y0, int x1, int y1) :A(x0, y0), B(x1, y1)
	{
		initialization_canvas();
	}
	line(point A_, point B_) :A(A_), B(B_)
	{
		initialization_canvas();
	}
	//два разных алгоритма 
	bool draw()
	{
		int deltax = abs(B.X - A.X);
		int deltay = abs(B.Y - A.Y);
		int error = 0;
		bool flag = (deltax >= deltay);
		if (((A.X > B.X) && (flag)) || ((A.Y > B.Y) && (!flag)))
			swap(A, B);
		int dir = flag ? ((B.Y - A.Y) > 0 ? 1 : -1) : ((B.X - A.X) > 0 ? 1 : -1);
		int delta = flag ? deltax : deltay;
		int deltaerr = flag ? deltay : deltax;
		int b = flag ? A.Y : A.X;
		int a_max = flag ? max(B.X, A.X) : max(B.Y, A.Y);
		int b_max = flag ? max(B.Y, A.Y) : max(B.X, A.X);;
		int a_min = flag ? min(B.X, A.X) : min(B.Y, A.Y);
		int b_min = flag ? min(B.Y, A.Y) : min(B.X, A.X);
		for (int a = a_min; a <= a_max; a++)
		{
			if (flag)
				Canvas->draw_pixel(a, b);
			else
				Canvas->draw_pixel(b, a);
			error += deltaerr;
			if (2 * error >= delta)
			{
				b += dir;
				error -= delta;
			}
		}
		return true;
	}
	bool draw2()
	{
		if (A.Y > B.Y)
			swap(A, B);
		point A0 = A;
		int deltaX = abs(B.X - A.X);
		int deltaY = abs(B.Y - A.Y);
		int signX = A.X < B.X ? 1 : -1;
		int signY = A.Y < B.Y ? 1 : -1;
		int error = deltaX - deltaY;
		bool exit = false;
		while (!exit)
		{
			Canvas->draw_pixel(A0.X, A0.Y);
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
		return true;
	}
};
class box
{
	point A, B;
	canvas* Canvas;
	//инициализация своего канваса, если он не был задан
	void initialization_canvas()
	{
		Canvas = new canvas(A, B);
	}
public:

	box(canvas& _Canvas, int x0, int  y0, int x1, int y1) :A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1))
	{
		Canvas = &_Canvas;
	}
	box(canvas& _Canvas, point A_, point B_) :A(min(A_.X, B_.X), min(A_.Y, B_.Y)), B(max(A_.X, B_.X), max(A_.Y, B_.Y))
	{
		Canvas = &_Canvas;
	}
	box(int x0, int  y0, int x1, int y1) :A(min(x0, x1), min(y0, y1)), B(max(x0, x1), max(y0, y1))
	{
		initialization_canvas();
	}
	box(point A_, point B_) :A(min(A_.X, B_.X), min(A_.Y, B_.Y)), B(max(A_.X, B_.X), max(A_.Y, B_.Y))
	{
		initialization_canvas();
	}
	//найти площадь
	float square(point& A_, point& B_)
	{
		return ((max(A_.X, B_.X) - min(A_.X, B_.X)) * (max(A_.Y, B_.Y) - min(A_.Y, B_.Y)));
	}
	float square(int& x0, int& y0, int& x1, int& y1)
	{
		return ((max(x0, x1) - min(x0, x1)) * (max(y0, y1) - min(y0, y1)));
	}
	float square()
	{
		return ((max(A.X, B.X) - min(A.X, B.X)) * (max(A.Y, B.Y) - min(A.Y, B.Y)));
	}
	//отрисовка границ 
	bool scope()
	{
		for (int i = A.X; i <= B.X; i++)
		{
			Canvas->draw_pixel(i, A.Y);
			Canvas->draw_pixel(i, B.Y);
		}
		for (int i = A.Y; i <= B.Y; i++)
		{
			Canvas->draw_pixel(A.X, i);
			Canvas->draw_pixel(B.X, i);
		}
		return true;
	}
	//закраска
	bool draw()
	{
		for (int i = A.Y; i <= B.Y; i++)
			for (int j = A.X; j <= B.X; j++)
				Canvas->draw_pixel(j, i);
		return true;
	}
};
class triangle
{
	point A, B, C;
	canvas* Canvas;
	bool gradient = true;
	//переопределение цвета для градиентного треугольника
	COLORREF get_color(int& x, int& y)
	{
		if (gradient)
		{
			double r_ = 0, g_ = 0, b_ = 0;
			double square_ = square();
			point G(x, y), A_(A), B_(B), C_(C);
			r_ = 255.0 * square(G, A_, C_) / square_;
			b_ = 255.0 * square(G, B_, C_) / square_;
			g_ = 255.0 * square(G, A_, B_) / square_;
			COLORREF color = RGB(r_, g_, b_);
			return color;
		}
		else
			return Canvas->get_color(x, y);

	}
	//сортировка вершин
	void sort(point& A_, point& B_, point& C_)
	{
		if (B_.Y < A_.Y)
			swap(B_, A_);
		if (C_.Y < A_.Y)
			swap(C_, A_);
		if (C_.Y < B_.Y)
			swap(C_, B_);
	}
	//инициализация своего канваса для градиента
	void initialization_canvas()
	{
		point D1, D2;
		D1.X = min(min(A.X, B.X), C.X);
		D1.Y = min(min(A.Y, B.Y), C.Y);
		D2.X = max(max(A.X, B.X), C.X);
		D2.Y = max(max(A.Y, B.Y), C.Y);
		Canvas = new canvas(D1, D2);
	}
public:
	triangle(canvas& _Canvas, int x0, int  y0, int x1, int y1, int x2, int y2) :A(x0, y0), B(x1, y1), C(x2, y2)
	{
		gradient = false;
		sort(A, B, C);
		Canvas = &_Canvas;
	}
	triangle(canvas& _Canvas, point A_, point B_, point C_) :A(A_), B(B_), C(C_)
	{
		gradient = false;
		sort(A, B, C);
		Canvas = &_Canvas;
	}
	triangle(int x0, int  y0, int x1, int y1, int x2, int y2) :A(x0, y0), B(x1, y1), C(x2, y2)
	{
		sort(A, B, C);
		initialization_canvas();
	}
	triangle(point A_, point B_, point C_) :A(A_), B(B_), C(C_)
	{
		sort(A, B, C);
		initialization_canvas();
	}
	void Rotate(float angle)
	{
		/*A.X = A.X * cos(alfa) - A.Y * sin(alfa);
		A.Y = A.X * sin(alfa) + A.Y * cos(alfa);
		B.X = B.X * cos(alfa) - B.Y * sin(alfa);
		B.Y = B.X * sin(alfa) + B.Y * cos(alfa);
		C.X = C.X * cos(alfa) - C.Y * sin(alfa);
		C.Y = C.X * sin(alfa) + C.Y * cos(alfa);*/
		float centerX = 195;
		float  centerY = 195;
		A.X = (A.X - centerX) * cos(angle) - (A.Y - centerY) * sin(angle) + centerX;
		A.Y = (A.X - centerX) * sin(angle) + (A.Y - centerY) * cos(angle) + centerY;
		B.X = (B.X - centerX) * cos(angle) - (B.Y - centerY) * sin(angle) + centerX;
		B.Y = (B.X - centerX) * sin(angle) + (B.Y - centerY) * cos(angle) + centerY;
		C.X = (C.X - centerX) * cos(angle) - (C.Y - centerY) * sin(angle) + centerX;
		C.Y = (C.X - centerX) * sin(angle) + (C.Y - centerY) * cos(angle) + centerY;
	}
	//найти площадь
	float square(int x0, int  y0, int x1, int y1, int x2, int y2)
	{
		return (0.5 * abs((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)));
	}
	float square(point A_, point B_, point C_)
	{
		return (0.5 * abs((B_.X - A_.X) * (C_.Y - A_.Y) - (C_.X - A_.X) * (B_.Y - A_.Y)));
	}
	float square()
	{
		return (0.5 * abs((B.X - A.X) * (C.Y - A.Y) - (C.X - A.X) * (B.Y - A.Y)));
	}
	//отрисовка границ 
	bool scope()
	{
		line Line1(*Canvas, A.X, A.Y, B.X, B.Y);
		Line1.draw();
		line Line2(*Canvas, A.X, A.Y, C.X, C.Y);
		Line2.draw();
		line Line3(*Canvas, B.X, B.Y, C.X, C.Y);
		Line3.draw();
		return true;
	}
	//закраска

	//алгоритм брезенхема
	bool draw()
	{
		point P1 = A, P2 = A;
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
				Canvas->draw_pixel(x, P2.Y, get_color(x, P2.Y));

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
				Canvas->draw_pixel(x, P2.Y, get_color(x, P2.Y));
		}
		return true;
	}
	//перебираем точки
	bool draw2()
	{
		int a, b, c;
		for (int j = min(min(A.X, B.X), C.X); j < max(max(A.X, B.X), C.X); j++)
			for (int i = min(min(A.Y, B.Y), C.Y); i < max(max(A.Y, B.Y), C.Y); i++)
			{
				a = (A.X - j) * (B.Y - A.Y) - (B.X - A.X) * (A.Y - i);
				b = (B.X - j) * (C.Y - B.Y) - (C.X - B.X) * (B.Y - i);
				c = (C.X - j) * (A.Y - C.Y) - (A.X - C.X) * (C.Y - i);
				if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
					Canvas->draw_pixel(j, i, get_color(j, i));
			}
		return true;
	}
	//вычисляем 
	bool draw3()
	{
		float P1 = 0, P2 = 0;
		float t = ((B.Y - A.Y) == 0 ? 1 : (B.Y - A.Y));
		for (int y = A.Y; y < B.Y; y++)
		{
			P1 = A.X + (B.X - A.X) * (y - A.Y) / t;
			P2 = A.X + (C.X - A.X) * (y - A.Y) / t;
			for (int x = min(P1, P2); x <= max(P1, P2); x++)
				Canvas->draw_pixel(x, y, get_color(x, y));
		}
		P1 = 0;
		P2 = 0;
		for (int y = B.Y; y < C.Y; y++)
		{
			P1 = B.X + (C.X - B.X) * (y - B.Y) / t;
			P2 = A.X + (C.X - A.X) * (y - A.Y) / t;
			for (int x = min(P1, P2); x <= max(P1, P2); x++)
				Canvas->draw_pixel(x, y, get_color(x, y));
		}
		return true;
	}
};
class circle
{
	point R;
	int radius;
	canvas* Canvas;
	//инициализация своего канваса, если он не был задан
	void initialization_canvas()
	{
		point A, B;
		A.X = R.X - radius;
		A.Y = R.Y - radius;
		B.X = R.X + radius;
		B.Y = R.Y + radius;
		Canvas = new canvas(A, B);
	}
public:
	circle(canvas& _Canvas, int x, int y, int radius_) :R(x, y), radius(radius_)
	{
		Canvas = &_Canvas;
	}
	circle(canvas& _Canvas, point R_, int radius_) :R(R_), radius(radius_)
	{
		Canvas = &_Canvas;
	}
	circle(int x, int y, int radius_) :R(x, y), radius(radius_)
	{
		initialization_canvas();
	}
	circle(point R_, int radius_) :R(R_), radius(radius_)
	{
		initialization_canvas();
	}
	//найти площадь
	float square(int& radius_)
	{
		return 3.14159265358979323846 * radius_ * radius_;
	}
	float square()
	{
		return 3.14159265358979323846 * radius * radius;
	}
	//отрисовка границ 
	void scope()
	{
		int x = 0;
		int y = radius;
		int delta = 1 - 2 * radius;
		int error = 0;
		while (y >= 0)
		{
			Canvas->draw_pixel(R.X + x, R.Y + y);
			Canvas->draw_pixel(R.X + x, R.Y - y);
			Canvas->draw_pixel(R.X - x, R.Y + y);
			Canvas->draw_pixel(R.X - x, R.Y - y);
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
			if (x < radius)
				++x;
			delta += 2 * (x - y);
			--y;
		}
	}
	//закраска
	void draw()
	{
		int x = 0;
		int y = radius;
		int delta = 1 - 2 * radius;
		int error = 0;
		while (y >= 0)
		{
			for (int i = R.X - x; i <= R.X + x; i++)
				Canvas->draw_pixel(i, R.Y + y);
			for (int i = R.X - x; i <= R.X + x; i++)
				Canvas->draw_pixel(i, R.Y - y);
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
			if (x < radius)
				++x;
			delta += 2 * (x - y);
			--y;
		}
	}
};
int main()
{
	cin.get();
	canvas Canvas_black(400, 400, RGB(0, 0, 0));
	canvas Canvas_green(400, 400, RGB(232, 124, 232));
	/*circle Circle_green(Canvas_green, 200, 150,150);
	circle Circle_black(Canvas_black, 200, 120, 160);
	circle Circle_glaz_L(Canvas_green, 100, 100, 50);
	circle Circle_glaz_R(Canvas_green,300, 100, 50);
	triangle Triangle(Canvas_green, 200, 130, 150, 230, 250, 230);*/
	circle Circle_green(200, 150, 150);
	circle Circle_black(Canvas_black, 200, 120, 160);
	circle Circle_glaz_L(100, 100, 50);
	circle Circle_glaz_R(300, 100, 50);
	triangle Triangle(200, 130, 150, 230, 250, 230);
	Circle_green.draw();
	Circle_black.draw();
	Circle_glaz_L.draw();
	Circle_glaz_R.draw();
	triangle Triangle2(Canvas_black, 200, 130, 150, 230, 250, 230);
	while (true)
	{

		Triangle.draw3();
		//	Triangle2.draw3();
		Triangle.Rotate(0.01);
		//Triangle2.Rotate(0.01);
		if (Triangle.square() == 0)
			break;
	}




	/*box Box(Canvas,10, 250, 150, 400);
	triangle Triangle(Canvas, 10, 250, 80, 180, 150, 250);
	circle Circle(Canvas, 250, 50, 40);
	line Line1(Canvas, 250, 50, 150, 100);
	line Line2(Canvas, 250, 50, 150, 50);
	line Line3(Canvas, 250, 50, 150, 150);
	line Line4(Canvas, 250, 50, 200, 175);

	Box.draw();
	Box.scope();
	Triangle.draw3();
	Circle.draw();
	Line1.draw();
	Line2.draw();
	Line3.draw();
	Line4.draw();*/

	//triangle Triangle(250, 10, 10, 200, 400, 300);
	//Triangle.draw3();
	//Triangle.scope();


	cin.get();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
