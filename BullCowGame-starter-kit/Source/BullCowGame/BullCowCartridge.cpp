// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"    //For hidden words
#include <cstdlib>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    //PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);// Debug Line   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{ 
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        ProcessGuess(Input);
    }
    
    
    // If No Show GameOver and HiddenWord?
    // Prompt To Play Again, Press Enter To Play Again?
    // Check User Input
    // PlayAgain Or Quit
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming The Player
    PrintLine(TEXT("Welcome to Bull Cows!\n"));
	
	/// Go through all the words, check their lenghts, and make sure they are isogram
	TArray<FString>ValidatedWords;
	for (int32 index = 0; index < WordList.Num(); index +=1)
	{
		if (WordList[index].Len() >= 4 && WordList[index].Len() <= 8)
		{
			if (IsIsogram(WordList[index]))
			{
				ValidatedWords.Emplace(WordList[index]);
			}
		}
	}

	HiddenWord = ValidatedWords[rand() % ValidatedWords.Num()];				//Chooses a random word from the list.
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i tries.\n"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...\n")); // Prompt Player For Guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again.\n"));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
	/// Clear the screen before showing next text
	UCartridge::ClearScreen();
	
	if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("Sorry wrong number of characters, \ntry guessing again!\n"));
		PrintLine(TEXT("The word is %i characters long.\n"), HiddenWord.Len());
		//PrintLine(TEXT("You have %i tries remaining\n"), Lives);
		return;
	}


    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("You haven't entered an isogram"));
        PrintLine(TEXT("Remember, no repeating letters.\n"));
        return;
    }


	// If is IsoGram, and Correct Length, but wrong word, remove a life.
	Lives -= 1;
	
	// Get Bulls and Cows
	int32 Bulls = 0; 
	int32 Cows = 0;
	GetBullsCows(Guess, HiddenWord, Bulls, Cows);					//OUT Parameter
	
	//Print Feedback
	PrintLine(TEXT("Your guess '%s' was incorrect!\n You have %i tries left.\n"), *Guess, Lives);
	PrintLine(TEXT("Bulls = %i, Cows = %i\n"), Bulls, Cows);

    if (Lives <= 0)
    {
        PrintLine(TEXT("You have no tries left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;   
    }
    
    // Show number of Bulls and Cows
    PrintLine(TEXT("Trying guessing again, \nyou have %i tries left.\n"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
	for (auto letter : Word)									//For each letter in the word passed
	{
		
		auto CheckedLetter = letter;							//Set the current letter to the letter
		int32 CheckingCount = 0;									//Start the count at 0.
		
		for (auto ComparingLetter : Word)						//For each letter in the word passed
		{
			
			if (CheckedLetter == ComparingLetter)				//Compare the current letter, to the letter in the word passed. If the same, +=1. 
			{
				CheckingCount += 1;
			}
		}

		if (CheckingCount >= 2)									//The count should never exceed 2, since we'll always find ourselfs (thus, add 1). 
		{
			return false;										//else, return false. 
		}
	}

    return true;
}

void UBullCowCartridge::GetBullsCows(const FString &GuessWord, const FString &HiddenWord,  int32 &Bulls, int32 &Cows)
{
	Bulls = 0;
	Cows = 0;

	for (int32 index = 0; index < GuessWord.Len(); index +=1)
	{
		for (int32 character = 0; character < HiddenWord.Len(); character += 1)
		{
			if (GuessWord[index] == HiddenWord[character])
			{
				if (index == character)
				{
					Bulls += 1;
				}
				else
				{
					Cows += 1;
				}
			}
		}
	}
}
