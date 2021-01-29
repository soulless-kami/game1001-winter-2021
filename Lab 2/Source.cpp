#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	float number1, number2, number3;

	cout << "Please enter your first number " << endl; 
	cin >> number1; 

	cout << "Please enter your second number " << endl;
	cin >> number2;

	cout << "Please enter your third number " << endl;
	cin >> number3;



	cout << "\nThe sum of the 3 numbers placed " << number1 + number2 + number3 << endl; 
	cout << "\nThe product of the 3 numbers placed " << number1 * number2 * number3 << endl;
	cout << "\nThe average of the 3 numbers placed " << number1 + number2 + number3 / 3 << endl;

	return 0;
}


