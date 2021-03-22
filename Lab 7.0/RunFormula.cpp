#include "Formula.h"
#include <iostream>

using namespace std;

int main()
{
	Rectangle Shape;

	double ShapeLenght, ShapeWidth;
	cout << "============================================================= \n";
	cout << "This program will calculate the variables of your rectangle. " << endl;
	cout << "============================================================= \n";
	
	cout << "============================================================= \n";
	cout << "Input your length: ";
	cin >> ShapeLenght;
	cout << "============================================================= \n";
	
	cout << "============================================================= \n";
	cout << "Input your Width: ";
	cin >> ShapeWidth;
	cout << "============================================================= \n";

	if (!Shape.setLenght(ShapeLenght))
	{
		cout << "Invalid input \n";
	}
	else if (!Shape.setWidth(ShapeWidth))
	{
		cout << "Invalid input \n";
	}
	else
	{
		cout << "============================================================= \n";
		cout << "This is the Lenght: " << Shape.getLenght() << endl;
		cout << "This is the Width: " << Shape.getWidth() << endl;
		cout << "This is the Area: " << Shape.getArea() << endl;
		cout << "This is the Perimeter: " << Shape.getPerimeter() << endl;
		cout << "============================================================= \n";
	}
	return 0;
}