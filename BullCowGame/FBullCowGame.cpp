#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()

{

	const FString HIDDEN_WORD = "planet"; // This MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;

}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const

{

	if (!IsIsogram(Guess)) // if the guess isn't an isogram

	{
		return EGuessStatus::Not_Isogram; 

	}

	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase 
	{

		return EGuessStatus::Not_Lowercase; 


	}

	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong

	{

		return EGuessStatus::Wrong_Length;

	}

	else

	{

		return EGuessStatus::OK;

	}

}

// receives a VALID guess, incriments turn, and returns count

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)

{

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {

		// compare letters against the guess

		for (int32 GChar = 0; GChar < WordLength; GChar++) {

			// if they match then

			if (Guess[GChar] == MyHiddenWord[MHWChar]) {

				if (MHWChar == GChar) { // if they're in the same place

					BullCowCount.Bulls++; // incriment bulls

				}

				else {

					BullCowCount.Cows++; // must be a cow

				}

			}

		}

	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;

}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() < 2) { return true; }
	
	TMap<char, bool> LettersSeen; // set up our map

	// loop through all letters in word
	for (auto Letter : Word)
	{
		//Letter = tolower(Letter); // handle mixed case

		// if the letter is in the map
		if (LettersSeen[Letter]) { return false; /* we do NOT have an isogram */ }
		else { LettersSeen[Letter] = true; /* add the letter to the map */ }

	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	TMap<char, bool> LowerLetters;
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
		else { return true; }
	}
	return true;
}
