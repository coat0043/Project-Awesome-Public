// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectAwesomeHUD.generated.h"

UCLASS()
class AProjectAwesomeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectAwesomeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

