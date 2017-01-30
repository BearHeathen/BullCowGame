/* This is the console executable, that makes use of the BullCow class

This acts as the view in a MVC pattern, and is responsible for all

user interaction. For game logic see the FBullCowGame class.

*/

#pragma once

#include <iostream>
#include <string>	
#include "FBullCowGame.h"

// Make syntax UE4 friendly.
using FText = std::string;
using int32 = int;

// Function prototypes as outside a class.
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which we reuse across plays

// the entry point for our application

int main()

{
	bool bPlayAgain = false;

	do {

		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();

	}

	while (bPlayAgain);
	return 0; // exit the application

}

// introduce the game

void PrintIntro()

{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}


// Plays a single game to completion
void PlayGame()

{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		// submit valid guess to the game, and receive counts
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

//Loop continually until user gives valid guess.
FText GetValidGuess() 

{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". "  << "Enter your guess: ";
		
		std::getline(std::cin, Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS! You won!\n\n";
	}
	else
	{
		std::cout << "TOO BAD! Better luck next time!\n\n";
	}
	
	return;
}

bool AskToPlayAgain()
{

	std::cout << "Do you want to play again with the same word (y/n)? ";

	FText Response = "";

	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');

}