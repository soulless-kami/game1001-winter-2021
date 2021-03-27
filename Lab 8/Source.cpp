#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Player
{
	string PlayerName;
	int att;
	int Hp = 50;
};

void ShowVectors(vector<int>);
void SortVectors(vector<int>&);

int main()
{
	Player Play1;
	cout << "=======================================\n";
	cout << "Enter your Adventure's name: ";
	cin >> Play1.PlayerName;
    cout << "=======================================\n";

	const int Size = 10 ;
	vector<int> Values(Size);
	srand(time(0));

	for (int i = 0; i < Size; i++)
	{
		Values[i] = rand() % 100 + 1;
	}
	SortVectors(Values);
	cout << "================================================\n";
	cout << "This is your selected chracter name: " << Play1.PlayerName << endl;
	cout << "================================================\n";
	
	int Random = Values[rand() % Values.size()];

	cout << "========================================\n";
	cout << "This is your starting health: " << Play1.Hp << endl;
	cout << "========================================\n";
	cout << "This is your starting attack power: " << Random << endl;
	cout << "========================================\n";

	return 0;
}

void SortVectors(vector<int>& Numbers)
{
	int Swap;
	int Temp;
	do
	{
		Swap = false;
		for (unsigned Count = 0; Count < Numbers.size() - 1; Count++)
		{
			if (Numbers[Count] > Numbers[Count + 1])
			{
				Temp = Numbers[Count];
				Numbers[Count] = Numbers[Count + 1];
				Numbers[Count + 1] = Temp;
				Swap = true;
			}

		}
		
	}
	while (Swap);
}
void ShowVector(vector<int> Numbers)
{
	for (unsigned Count = 0; Count < Numbers.size(); Count++)
	{
		cout << Numbers[Count] << " ";
		cout << endl;
	}
}