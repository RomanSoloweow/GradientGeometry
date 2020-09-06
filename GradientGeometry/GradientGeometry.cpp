#include <iostream> 
#include "Box.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"
using namespace std;

int main()
{
	cout << ("Press any key to start:");
	getchar();

	Canvas canvas(10, 10, 1500, 1500);
	Box Box1(10, 10, 1500, 1500);
	Box Box2(1000, 1000, 1500, 1500);
	Triangle Triangle(10, 250, 80, 180, 150, 250);
	Circle Circle(350, 350, 150);
	Line Line1(50, 50, 300, 1500);
	Line Line2(5, 10, 1495, 1500);
	Line Line3(250, 50, 150, 150);
	Line Line4(250, 50, 200, 175);
	canvas.FillFigure(Line1);
	//canvas.FillFigure(Line2, false);
	/*canvas.FillFigure(Box2, false);*/
	//canvas.FillFigure(Triangle);
	//canvas.FillFigure(Circle);
	//canvas.FillFigure(Line1);
	//canvas.FillFigure(Line2);
	//canvas.FillFigure(Line3);
	//canvas.FillFigure(Line4);

	/*Triangle Triangle(250, 10, 10, 200, 400, 300);*/
	/*Triangle.draw();*/
	//Triangle.scope();


	//cin.get();
	cout << ("Press '1' for end:");
	char c;
	do
	{
	 c = getchar();
	}while (c != '1');
	
	return 0;
}
