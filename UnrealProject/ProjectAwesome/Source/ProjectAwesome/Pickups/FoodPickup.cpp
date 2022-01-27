// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodPickup.h"
#include "../ProjectAwesomeGameMode.h"

AFoodPickup::AFoodPickup()
{
    FoodValue = 5;
}

void AFoodPickup::OnPickUp()
{
    AProjectAwesomeGameMode* GMode = Cast<AProjectAwesomeGameMode>(GetWorld()->GetAuthGameMode());

    GMode->FoodTotal += FoodValue;
    Disable();
}