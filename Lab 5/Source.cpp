#include <iostream>
#include <vector> 

using namespace std; 

int main()
{
	const int NumberSize = 10;
	int Number[NumberSize];
	int LowNumberSize = 0;
	int HighNumberSize = 0;
	int x;
	int Average;
	int SumOfAll = 0;
	
	vector<int>LowNumber(10);
	vector<int>HighNumber(10);

	cout << "=========================\n";
	cout << "Insert your 10 numbers\n";
	cout << "=========================\n";
	
	for (x = 0; x < NumberSize; x++)
	{
		cin >> Number[x];
		SumOfAll += Number[x];
	}
	
	Average = SumOfAll / 10;
	cout << "========================================================================\n";
	cout << "The average of the following numbers place are.\n" << Average << endl;
	cout << "========================================================================\n";
	
	
	cout << "========================================================================\n";
	cout << "The following numbers are the lower than average numbers.\n";
	
	for (int LowNumber : Number) {
		if (LowNumber <= Average)
		{
			cout << LowNumber << ",";

		}
	}
	cout << "\n========================================================================\n";
	
	cout << endl;
	cout << "========================================================================\n";

	cout << "The following numbers are the higher than average numbers.\n";
	for (int HighNumber : Number) {
		if (HighNumber > Average) {
			cout << HighNumber << ",";
		}
	}
	cout << "\n========================================================================\n";

	return 0;



}
