// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItemPickup.h"

AKeyItemPickup::AKeyItemPickup()
{
    bCanBeDropped = false;

    Tags.Add("KeyItem");
}

void AKeyItemPickup::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AKeyItemPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AKeyItemPickup::PostInitializeComponents()
{
    Super::PostInitializeComponents();

}


void AKeyItemPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
