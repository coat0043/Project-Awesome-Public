// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyItemPickup.h"
#include "../GlobalDataForProject.h"
#include "PuzzlePiece.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAWESOME_API APuzzlePiece : public AKeyItemPickup
{
	GENERATED_BODY()

public:
	APuzzlePiece();

	void OnPickUp();

protected:


	//Enum for keyitems
	//Set in blueprints
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	KeyItemTypes Type;
	
private:
	void SetPuzzleFlagToTrue();
};
