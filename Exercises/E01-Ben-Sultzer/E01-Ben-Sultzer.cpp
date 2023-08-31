// Course:			IGME 309
// Student Name:	Ben Sultzer
// Friday Exercise:	01

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

bool g_is_running = true;

// Generate a random number within the range of 1 to 100, both numbers inclusive,
// and then return it.
int GenerateRandomNumber() {
	int targetNumber = 0;

	/**********************************/
	// write your code below 
	targetNumber = rand() % 100 + 1;

	// write your code above
	/**********************************/

	cout << "A random target number is generated!" << endl;
	return targetNumber;
}

// Read the player's input number
// and return the entered value.
int PlayerEnterANumber() {
	int playerNumber = 0;

	cout << "Enter a number (-1 to quit): ";

	// Your code don't need to handle the '-1' input,
	// it will be handled by the provided Gameloop() function.
	/**********************************/
	// write your code below 
	cin >> playerNumber;

	// write your code above
	/**********************************/

	return playerNumber;
}

// Examine the player's guess in relation to the target number:
// Return 0 if the guess is correct. 
// Return 1 if the guess is lower than the target number. 
// Return 2 if the guess is high than the target number.
int HighOrLow(int targetNumber, int playerNumber) {
	/**********************************/
	// write your code below
	if (playerNumber == targetNumber) {
		return 0;
	}
	else if (playerNumber < targetNumber) {
		return 1;
	}
	else {
		return 2;
	}

	// write your code above
	/**********************************/
}

void GameLoop() {
	// generate a random target number
	int targetNumber = GenerateRandomNumber();

	// Player's guess loop
	while (g_is_running) {
		// Player enter a number
		int playerNumber = PlayerEnterANumber();
		if (playerNumber == -1) {
			g_is_running = false; // get -1, quit the game
			return;
		}

		// Examine the number is high or low
		int hilo = HighOrLow(targetNumber, playerNumber);

		if (hilo == 0) {
			cout << "Your guess is correct! The number of guess is " << targetNumber << "." << endl;
			break;	// Guess is correct, break the guess loop 
		}
		else if (hilo == 1) {
			cout << "Your guess is low." << endl;
		}
		else if (hilo == 2) {
			cout << "Your guess is high." << endl;
		}
	}

	// Continue play or not
	cout << "Continue to play? (y/n)" << endl;
	char sentinel;
	cin >> sentinel;
	if (sentinel != 'y')
		g_is_running = false;
	return;
}

int main() {
	// Initialize random seed
	srand(time(0));

	cout << "Welcome to the Game!" << endl;
	cout << "Please guess the number between 1 and 100." << endl;
	cout << "*****************************************" << endl << endl;

	do {
		GameLoop();
		cout << "*****************************************" << endl << endl;
	} while (g_is_running);

	cout << "Game End" << endl;

	return 0;
}