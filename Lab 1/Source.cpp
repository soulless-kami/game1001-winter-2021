// Simple C++ program
#include <iostream>
using namespace std;    //use standard namespace 

//main entry point to app
int main()
{
	cout << "The size of the following datas\n\n\n";


	cout << "The size of a bool: " << sizeof(bool) << " bytes. \n";
	cout << "The size of a char: " << sizeof(char) << " bytes. \n";
	cout << "The size of a short int: " << sizeof(short int) << " bytes. \n";
	cout << "The size of a float: " << sizeof(float) << " bytes. \n";
	cout << "The size of a int: " << sizeof(int) << " bytes. \n";
	cout << "The size of a long int: " << sizeof(long int) << " bytes. \n";
	cout << "The size of a double: " << sizeof(double) << " bytes. \n";
	cout << "The size of a long long int: " << sizeof(long long int) << " bytes. \n";
	cout << "The size of a string: " << sizeof(string) << " bytes. \n\n\n";

	
	
	cout << "A short demonstrating of the following operations\n\n\n";

	double first = 2,
		second = 4,
		third = 6,
		fourth = 8,
		answerAddition,
		answerSubtraction,
		answerMultiplication,
		answerDivision,
		answerModulous;



	cout << "Addition: " << first + second << endl;
	cout << "Substraction: " << second - third << endl;
	cout << "Multiplication " << third * fourth << endl;
	cout << "Division " << first / fourth << endl;
	cout << "Modulous " << (int)first % (int)second << endl;
	




	return 0;
}