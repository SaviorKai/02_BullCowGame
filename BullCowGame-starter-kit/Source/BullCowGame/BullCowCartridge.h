// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString &Guess);
	bool IsIsogram(const FString &Word) const;								// Remember that const functions can't call other functions that aren't const. It can also not change any MEMBER VARIBLES
	void GetBullsCows(const FString &GuessWord, const FString &HiddenWord, int32& Bulls, int32& Cows);					// Out Parameters on bulls and cows

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
};