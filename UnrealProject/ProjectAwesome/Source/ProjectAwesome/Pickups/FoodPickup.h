// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPickupObject.h"
#include "FoodPickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAWESOME_API AFoodPickup : public ABasicPickupObject
{
	GENERATED_BODY()
public:
	AFoodPickup();

	void OnPickUp();

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	int FoodValue;
};
