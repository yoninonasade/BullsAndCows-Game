/*
this in the consol executable , that makes us of the FBullCowGame class
this acts as the view in a MVC patern , and is responsible for all
user int32eraction.For game logic see the FBullCowGame class.

*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = FString;
using int32 = int;

void Print_intro(); // int32roduce the game 
FText Get_Valid_Guess(); // get a guess from the player 
void Play_Game(); // main function
bool Ask_To_Play_Againe(); // return true to continue playing or false to exit 
void PrintGameSummary();


FBullCowGame BCGame;

int main() {

	do {

		Print_intro();
		Play_Game();

	} while (Ask_To_Play_Againe());

	return 0;
}

void Print_intro()
{
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.Get_Hiddin_Word_Length() << " letter isogram I'm thinking of?\n";
	return;
}
FText Get_Valid_Guess()
{

	EGuessStatus GuessStatus = EGuessStatus::Invalid_status;
	FText Guess = "";

	do {
		int32 currentTry = BCGame.Get_current_try();
		std::cout << "Try " << currentTry << ". Enter your guess\n";
		std::getline(std::cin, Guess);
		GuessStatus = BCGame.CheckGuessValidity(Guess);

		switch (GuessStatus)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please Enter a word without repeting letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a " << BCGame.Get_Hiddin_Word_Length() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assuming the Guess is Valid 
			break;
		}

		std::cout << std::endl;
	} while (GuessStatus != EGuessStatus::OK); // keep looping until valid input

	return Guess;
}
void Play_Game() {

	BCGame.Reset();
	int32 maxTries = BCGame.Get_Max_Tries();

	while (!BCGame.ISGameWon() && BCGame.Get_current_try() <= maxTries)
	{
		FText Guess = Get_Valid_Guess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bull = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}


	PrintGameSummary();
	return;

}
bool Ask_To_Play_Againe() {

	FText Response = "";
	std::cout << "Do you want to play again? ";
	std::getline(std::cin, Response);

	return ((Response[0] == 'Y') || (Response[0] == 'y'));
}

void PrintGameSummary()
{
	if (BCGame.ISGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}