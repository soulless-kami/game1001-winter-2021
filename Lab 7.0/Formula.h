#pragma once


class Rectangle
{
private:
	double Length;
	double Width;

public:
    bool setLenght(double);
    bool setWidth(double);

	double getLenght() { return Length; }
	double getWidth() { return Width; }
	double getArea() { return Length * Width; }
	double getPerimeter() { return 2 * (Width + Length); }
};