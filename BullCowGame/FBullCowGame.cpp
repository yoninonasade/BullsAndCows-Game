#pragma once

#include "FBullCowGame.h"

#include <map>
#define TMap std::map  


bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> letterSeen;
	for (auto letter : word) // for all letters of the word
	{
		letter = tolower(letter);
		if (letterSeen[letter])
		{
			return false;
		}
		else
		{
			letterSeen[letter] = true;
		}

	}
	return true;
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto letter : word)
	{
		if (!islower(letter))
		{
			return false;
		}
	}

	return true;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	constexpr int32 CURRENT_TRY = 1;
	const FString HIDDIN_WORD = "ant";
	bGameIsWOn = false;

	m_hidden_word = HIDDIN_WORD;
	m_current_try = CURRENT_TRY;
	m_max_tries = MAX_TRIES;

	return;
}

int32 FBullCowGame::Get_Max_Tries() const
{
	return m_max_tries;
}

int32 FBullCowGame::Get_current_try() const
{
	return m_current_try;
}

int32 FBullCowGame::Get_Hiddin_Word_Length() const
{
	return m_hidden_word.length();
}

bool FBullCowGame::ISGameWon()
{
	return bGameIsWOn;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{

	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != Get_Hiddin_Word_Length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	m_current_try++;
	FBullCowCount BullCowCount;
	int32 HiddinWordLength = m_hidden_word.length();


	for (int32 MHWChar = 0; MHWChar < HiddinWordLength; MHWChar++)
	{
		// loop through all letters in the guess word 
		for (int32 GChar = 0; GChar < HiddinWordLength; GChar++)
		{
			// compare leeters aginst hiddin word 
			if (guess[GChar] == m_hidden_word[MHWChar]) {

				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddinWordLength) {

		bGameIsWOn = true;
	}
	else
	{
		bGameIsWOn = false;
	}

	return BullCowCount;
}