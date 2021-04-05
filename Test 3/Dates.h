#pragma once

class Dates
{
private: 
	bool Input = true;
	int array [12]{ 31,0,31,30,31,30,31,31,30,31,30,31 };
	int Month, Year;

public:
	bool setMonth(int);
	bool setYear(int);

	int getMonth() { return Month; }
	int getYear() { return Year; }
	int getDay() { return array[Month - 1]; }
};