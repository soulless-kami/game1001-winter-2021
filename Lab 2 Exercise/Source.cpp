#include <ctime>
#include <iostream> // Console input/output.
#include <string>   // Using strings.
using namespace std;

int main() // Entry point for every C++ program.
{
	// Declare variables.
	bool currentPlayer, quitGame = false;
	int randomNum, guess;
	string player1, player2;
	// Create random number from 1 to 100 inclusive.
	srand((unsigned)time(NULL)); // Seeds the random number sequence.
	randomNum = 1 + rand() % 100; // Returns 1-100 inclusive


	// Prompt the players for their names.
	cout << "Player 1, enter your name: ";
	cin >> player1;
	cout << "Okay, your name is " << player1 << endl;
	cout << "Player 2, enter your name: ";
	cin >> player2;
	cout << "Okay, your name is " << player2 << endl;

	// Randomize who goes first. You can also use a Boolean.
	currentPlayer = rand() % 2; // Sets currently player to 0 or 1. 

	bool player2First = currentPlayer;
	bool restart = false;
	int choice = 0;
	int guessLimit = 5;
	int guessLimit1 = guessLimit;
	int guessLimit2 = guessLimit;
	bool first = true;

	// Start the game. Main game loop.
	while (quitGame == false) // !quitGame or quitGame != true
	{   // The ?: below is the conditional operator. It's a mini if/else.

		if (restart) {
			restart = false;
			randomNum = 1 + rand() % 100; // Returns 1-100 inclusive
			guessLimit1 = guessLimit;
			guessLimit2 = guessLimit;
		}

		cout << (currentPlayer == 0 ? player1 : player2) << ", enter your guess: ";
		cin >> guess; // cin is dangerous. We're not accounting for fail.
		// Check the guess against three possibilities.
		if (guess < randomNum) {
			if (first) {
				guessLimit1--;
				first = false;
			}
			else {
				guessLimit2--;
				first = true;
			}
			cout << "Your guess is too low." << endl;
			if (player2First) {
				cout << "------------------------------------------------------" << endl;
				cout << player2 << " has " << guessLimit1 << " guess remaining." << endl;
				cout << player1 << " has " << guessLimit2 << " guess remaining." << endl;
				cout << "------------------------------------------------------" << endl;
			}
			else {
				cout << "------------------------------------------------------" << endl;
				cout << player1 << " has " << guessLimit1 << " guess remaining." << endl;
				cout << player2 << " has " << guessLimit2 << " guess remaining." << endl;
				cout << "------------------------------------------------------" << endl;
			}

		}
		else if (guess > randomNum) {
			if (first) {
				guessLimit1--;
				first = false;
			}
			else {
				guessLimit2--;
				first = true;
			}
			cout << "Your guess is too high." << endl;
			if (player2First) {
				cout << "------------------------------------------------------" << endl;
				cout << player2 << " has " << guessLimit1 << " guess remaining." << endl;
				cout << player1 << " has " << guessLimit2 << " guess remaining." << endl;
				cout << "------------------------------------------------------" << endl;
			}
			else {
				cout << "------------------------------------------------------" << endl;
				cout << player1 << " has " << guessLimit1 << " guess remaining." << endl;
				cout << player2 << " has " << guessLimit2 << " guess remaining." << endl;
				cout << "------------------------------------------------------" << endl;
			}
		}
		else // guess == randomNum
		{
			cout << "Your guess is correct!" << endl;

			cout << "Restart game? (Type number for choice)" << endl;
			cout << "------------------------------------------------------" << endl;
			cout << "1. Yes)" << endl;
			cout << "2. No)" << endl;

			cin >> choice;

			if (choice == 2) {
				quitGame = true;
			}
			else {
				restart = true;
			}

		}

		if (guessLimit1 <= 0 && guessLimit2 <= 0) {
			cout << "Out of guesses for both players, the number was: " << randomNum << endl;

			cout << "Restart game? (Type number for choice)" << endl;
			cout << "------------------------------------------------------" << endl;
			cout << "1. Yes)" << endl;
			cout << "2. No)" << endl;

			cin >> choice;

			if (choice == 2) {
				quitGame = true;
			}
			else {
				restart = true;
			}
		}

		if (quitGame == false) // Game is still on, switch player.
			currentPlayer = !currentPlayer;
	}
	cout << (currentPlayer == 0 ? player1 : player2) << " wins!" << endl;

	system("pause"); // Pause the console before closing. Not portable.
	return 0;
}