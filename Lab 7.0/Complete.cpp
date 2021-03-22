#include "Formula.h"
#include <iostream>

using namespace std;

bool Rectangle::setLenght(double len)
{
	bool ValidData = true;
    if (len >= 0)
	{
		Length = len;
	}
	else
	{
		ValidData = false;
	}
	return ValidData;
}

bool Rectangle::setWidth(double wid)
{
	bool ValidData = true;
	if (wid >= 0.0)
	{
		Width = wid;
	}
	else
	{
		ValidData = false;
	}
	return ValidData;
}