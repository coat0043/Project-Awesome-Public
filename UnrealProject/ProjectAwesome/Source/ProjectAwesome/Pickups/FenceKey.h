// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyItemPickup.h"
#include "../GlobalDataForProject.h"
#include "FenceKey.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAWESOME_API AFenceKey : public AKeyItemPickup
{
	GENERATED_BODY()
public:
	AFenceKey();

	
	void OnPickUp();

protected:
	

	//Enum for keyitems
	KeyItemTypes Type;
};
