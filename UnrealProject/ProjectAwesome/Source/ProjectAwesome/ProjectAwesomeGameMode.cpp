// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAwesomeGameMode.h"
#include "ProjectAwesomeHUD.h"
#include "ProjectAwesomeCharacter.h"
#include "CustomPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AProjectAwesomeGameMode::AProjectAwesomeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectAwesomeHUD::StaticClass();

	
	/*static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/Blueprints/BP_CustomPlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;*/

	//PlayerControllerClass = ACustomPlayerController::StaticClass();

   

	bIsRecordingPickedUp = false;
	bIsFenceKeyPickedUp = false;

	bIsPuzzlePiece01PickedUp = false;
	bIsPuzzlePiece02PickedUp = false;
	bIsPuzzlePiece03PickedUp = false;
	bIsPuzzlePiece04PickedUp = false;
	bIsPuzzlePiece05PickedUp = false;
	bIsPuzzlePiece06PickedUp = false;
	bIsPuzzlePiece07PickedUp = false;
	bIsPuzzlePiece08PickedUp = false;
	bIsPuzzlePiece09PickedUp = false;

	bIsPlayerActive = false;
	FoodTotal = 0;
}



bool AProjectAwesomeGameMode::GetIsPlayerActive()
{
	return bIsPlayerActive;
}

void AProjectAwesomeGameMode::ToggleIsPlayerActive()
{
	bIsPlayerActive = !bIsPlayerActive;
}
