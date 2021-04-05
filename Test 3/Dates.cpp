#include "Dates.h"
#include <iostream>

using namespace std;

bool Dates::setMonth(int Months)
{
	bool Data = true;
	if (Months >= 0)
	{
		Month = Months;
	}
	else 
	{
		Data = false;
	}
	return Data;
}

bool Dates::setYear(int Years)
{
	bool Data = true;
	if (Years >= 0)
	{
		Year = Years;
	}
	else
	{
		Data = false;
	}
	return Data;
}


