#pragma once

#include <string>

using FString = std::string;
using int32 = int;

enum class EGuessStatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


class FBullCowGame {

private:

	int32 m_current_try;
	int32 m_max_tries;
	FString m_hidden_word;
	bool bGameIsWOn;

	bool IsIsogram(FString)const;
	bool IsLowercase(FString)const;


public:

	FBullCowGame();  // costructor  
	void Reset(); // reset object values

				  // Geters // 
	int32 Get_Max_Tries()const;
	int32 Get_current_try()const;
	int32 Get_Hiddin_Word_Length()const;


	bool ISGameWon();
	EGuessStatus CheckGuessValidity(FString)const;
	FBullCowCount SubmitValidGuess(FString); // count bulls and cows and increse try # assunimg valid guess

};