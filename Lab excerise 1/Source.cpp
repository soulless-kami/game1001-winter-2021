#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double HoursWorked = 0;
	double HourlyRate = 0;
	double OvertimeHours = 0;


	cout << "Please enter how many hours you worked today\n ";
	cin >> HoursWorked;

	cout << "Now please enter your hourly rate\n ";
	cin >> HourlyRate;


	if (HoursWorked > 40)
	{
		OvertimeHours = HoursWorked - 40;
		HoursWorked = 40;
	}

	double result1 = HoursWorked * HourlyRate;
	double result2 = (OvertimeHours * HourlyRate) * 1.5;
	double result3 = result1 + result2;

	cout << "Your total regular pay for the week is " << result1 << " dollars\n ";
	cout << "Your total overtime pay for this week is  " << result2 << " dollars\n ";
	cout << "Your total pay for the week is " << result3 << " dollars\n ";
	return 0;
}