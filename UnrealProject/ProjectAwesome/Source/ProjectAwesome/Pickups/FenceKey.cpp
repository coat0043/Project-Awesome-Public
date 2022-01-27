// Fill out your copyright notice in the Description page of Project Settings.


#include "FenceKey.h"
#include "../ProjectAwesomeGameMode.h"

AFenceKey::AFenceKey()
{
    Type = KeyItemTypes::FenceKey;
}

void AFenceKey::OnPickUp()
{
    AProjectAwesomeGameMode* GMode = Cast<AProjectAwesomeGameMode>(GetWorld()->GetAuthGameMode());
    GMode->bIsFenceKeyPickedUp = true;

    Disable();
}
