#include <iostream> 
#include "Box.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"
using namespace std;

int main()
{
	cout << ("Press any key to start:");
	cin.get();

	Canvas canvas(10, 10, 1500, 1500);
	Box Box(10, 250, 150, 400);
	Triangle Triangle(10, 250, 80, 180, 150, 250);
	Circle Circle(250, 50, 40);
	Line Line1(250, 50, 150, 100);
	Line Line2(250, 50, 150, 50);
	Line Line3(250, 50, 150, 150);
	Line Line4(250, 50, 200, 175);

	canvas.DrawFigure(Box);
	canvas.DrawFigure(Triangle);
	canvas.DrawFigure(Circle);
	canvas.DrawFigure(Line1);
	canvas.DrawFigure(Line2);
	canvas.DrawFigure(Line3);
	canvas.DrawFigure(Line4);

	/*Triangle Triangle(250, 10, 10, 200, 400, 300);*/
	/*Triangle.draw();*/
	//Triangle.scope();


	cin.get();
	return 0;
}
