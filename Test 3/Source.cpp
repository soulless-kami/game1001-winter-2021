#include <iostream>
#include "Dates.h"

using namespace std;

int main()
{
	Dates Date;

	int Month, Year;
	bool Input = true;

	cout << "============================================================================\n";
	cout << "This program will display the days in any selected month you choose from.\n";
	cout << "To end the program please input 0 0.\n";
	cout << "============================================================================\n";

	do
	{
		cout << "===============================\n";
		cout << "Enter a month and year: ";
		cin >> Month >> Year;
		cout << "===============================";

		if (!Date.setMonth(Month))
		{
			cout << "Invalid input" << endl;
		}
		else if (!Date.setYear(Year))
		{
			cout << "Invalid input" << endl;
		}
		if (Month != 2 && Month != 0)
		{
			cout << endl << "There are " << Date.getDay() << " days in the selected month. " << endl;
		}
		else if (Month == 2)
		{
			if (Year % 4 == 0)
			{
				if (Year % 100 == 0)
				{
					if (Year % 400 == 0)
						cout << endl << "There are 29 days in the selected month. " << endl;
					else
						cout << endl << "There are 28 days in the selected month. " << endl;
				}
				else
					cout << endl << "There are 29 days in the selected month. " << endl;
			}
			else
				cout << endl << "There are 28 days in the selected month. " << endl;
		}
		else if (Month == 00)
		{
			Input = false;
		}
		else
		{
			cout << endl << "Please retry" << endl;
		}
	} while (Input);

	return 0;
}