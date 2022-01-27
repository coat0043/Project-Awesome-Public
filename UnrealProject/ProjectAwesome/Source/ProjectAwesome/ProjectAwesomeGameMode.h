// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectAwesomeGameMode.generated.h"

UCLASS()
class AProjectAwesomeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectAwesomeGameMode();

	bool bIsRecordingPickedUp;
	bool bIsFenceKeyPickedUp;
	bool bIsPuzzlePiece01PickedUp;
	bool bIsPuzzlePiece02PickedUp;
	bool bIsPuzzlePiece03PickedUp;
	bool bIsPuzzlePiece04PickedUp;
	bool bIsPuzzlePiece05PickedUp;
	bool bIsPuzzlePiece06PickedUp;
	bool bIsPuzzlePiece07PickedUp;
	bool bIsPuzzlePiece08PickedUp;
	bool bIsPuzzlePiece09PickedUp;

	bool bIsPlayerActive;
	int FoodTotal;
	UFUNCTION(BlueprintCallable, Category = "PlayerActive" )
		bool GetIsPlayerActive();
	UFUNCTION(BlueprintCallable, Category = "TogglePlayerActive")
		void ToggleIsPlayerActive();

};



