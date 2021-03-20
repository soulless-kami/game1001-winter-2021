#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int First,
		Second,
		Third,
		Fourth,
		Fifth;

	void DisplayAsterisks();
	{
		cout << "=================================================================\n";
		cout << "Input your five variables, they must stay in the range of 1-30.\n";
		cout << "=================================================================\n";
		cin >> First >> Second >> Third >> Fourth >> Fifth;
	}
	cout << "=================================================================\n";
	for(int x = 1; x<= First; x++)
	{
		cout << "*";
	}
	cout << endl;
	
	for (int x = 1; x <= Second; x++)
	{
		cout << "*";
	}
	cout << endl;

	for (int x = 1; x <= Third; x++)
	{
		cout << "*";
	}
	cout << endl;

	for (int x = 1; x <= Fourth; x++)
	{
		cout << "*";
	}
	cout << endl;

	for (int x = 1; x <= Fifth; x++)
	{
		cout << "*";
	}
	cout << endl;

	cout << "=================================================================\n";
	cout << "These are your variables show as a bar graph.\n";

}



