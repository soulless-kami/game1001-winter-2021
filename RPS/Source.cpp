#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int RPS;
	const int Size = 70;
	int PlayerScore = 0;
	int CPUScore = 0;
	char Player[Size];

	string FileName;
	string Score;
	string Play;

	cout << "---------------------------------------------------\n";
	cout << "Care for a game of Rock, Paper, Scissors?\n";
	cout << "I must know your name first, what is it?" << endl;
	cout << "---------------------------------------------------\n";
	
	cin.getline(Player, Size); 
	cout << "--------------------------------------------------------------------------------------------------------\n";
	cout << Player << " What a wonderful name, now if we may begin pick between 1 rock, 2 paper, or 3 scissors :3\n";
	cout << "--------------------------------------------------------------------------------------------------------\n";

	ifstream InputFile;
	ofstream OutputFile;
	
	FileName = Player; 

	OutputFile.open(FileName+".txt");

	bool PlayAgain = true;
	if (Play == "y" || Play == "Y") {
		PlayAgain = true;
	}
	while (PlayAgain != false) {
		{
			srand(time(NULL));

			int CPU = rand() % 3 + 1;
			char Restart;
			cout << "You choose first, dont worry i wont cheat :3\n";
			cout << "-----------------------------------------------------------\n";
			cin >> RPS;
			if (CPU == 1)
			{
				cout << "I choose Rock ";
			}
			else if (CPU == 2)
			{
				cout << "I choose Paper ";
			}
			else if (CPU == 3)
			{
				cout << "I choose Scissors ";
			}
			if (RPS == CPU)
			{
				cout << "A draw, well thats a shame :c " << endl;
			}

			else if
				(RPS == 1 && CPU == 3)
			{
				PlayerScore++;
				cout << "You won :O " << endl;
			}

			else if (RPS == 2 && CPU == 1)
			{
				PlayerScore++;
				cout << "You won :O " << endl;
			}

			else if (RPS == 3 && CPU == 2)
			{
				PlayerScore++;
				cout << "You won :O " << endl;
			}
			else
			{
				CPUScore++;
				cout << "It would appear you lost this time :c " << endl;
			}
			cout << "---------------------------------------------------------------------------------\n";
			cout << endl << endl << Player << " Would you like to play another game with me? (N/Y): ";
			cin >> Play;
			if (Play == "n" || Play == "N") {
				PlayAgain = false;
			}
			else if (Play == "y" || Play == "Y") {
			}

		}

	}
	OutputFile << "The CPU score:" << CPUScore << "\n" << Player << "Score:" << PlayerScore << endl;
	cout << "The CPU has won a total of " << CPUScore << " times.\n" << Player << " has won a total of " << PlayerScore << " times.\n";
	
	OutputFile.close();

	InputFile.open(FileName+".txt");

	(getline(InputFile, Score));
	
	cout << "I hope to play again soon :3 " << endl;

	InputFile.close();

		return 0;
}