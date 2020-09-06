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


	Canvas canvas;
	Triangle Triangle(1500, 100, 100, 1900, 2900, 1900);
	Circle Circle(1500, 1000, 900);
	Box Box(100, 100, 2900, 1900);
	Line Line1(100, 100, 2900, 1900);
	Line Line2(2900, 100, 100, 1900);
	canvas.DrawFigure(Line1);
	canvas.DrawFigure(Line2);



	cout << ("Press '1' for end:");
	char c;
	do
	{
	 c = getchar();
	}while (c != '1');
	
	return 0;
}
