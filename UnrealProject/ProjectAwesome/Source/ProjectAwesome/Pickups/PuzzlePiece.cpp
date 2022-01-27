// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePiece.h"
#include "../ProjectAwesomeGameMode.h"

APuzzlePiece::APuzzlePiece()
{
    //Default should be changed in blueprints
   // Type = KeyItemTypes::PuzzlePiece01;

}



void APuzzlePiece::OnPickUp()
{
    SetPuzzleFlagToTrue();
    Disable();

}

void APuzzlePiece::SetPuzzleFlagToTrue()
{
    AProjectAwesomeGameMode* GMode = Cast<AProjectAwesomeGameMode>(GetWorld()->GetAuthGameMode());

    if (Type == KeyItemTypes::PuzzlePiece01) {
        GMode->bIsPuzzlePiece01PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece02) {
        GMode->bIsPuzzlePiece02PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece03) {
        GMode->bIsPuzzlePiece03PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece04) {
        GMode->bIsPuzzlePiece04PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece05) {
        GMode->bIsPuzzlePiece05PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece06) {
        GMode->bIsPuzzlePiece06PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece07) {
        GMode->bIsPuzzlePiece07PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece08) {
        GMode->bIsPuzzlePiece08PickedUp = true;
    }

    else if (Type == KeyItemTypes::PuzzlePiece09) {
        GMode->bIsPuzzlePiece09PickedUp = true;
    }
}