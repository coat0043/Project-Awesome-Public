// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPickupObject.h"
#include "KeyItemPickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAWESOME_API AKeyItemPickup : public ABasicPickupObject
{
	GENERATED_BODY()

public:
	
		AKeyItemPickup();
	
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
