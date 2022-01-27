// Fill out your copyright notice in the Description page of Project Settings.
/*
Author : Scott Kennedy
Date Modified : 3 / 29 / 2021
Comment / Description : Player input Controller
ChangeLog :
        - Creation of CustomPlayerController
		- Moved Player Input into a custom player controller
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

class UInputComponent;
/**
 * 
 */
UCLASS()
class PROJECTAWESOME_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;

protected:
    virtual void SetupInputComponent() override;

    virtual void AcknowledgePossession(APawn* PossesedPawn) override;

    
    void OnResetVR();

    void MoveForward(float Val);

    void MoveRight(float Val);

    void TurnAtRate(float Val);

    void LookUpAtRate(float Val);

    void RaycastPressed();

    void RaycastReleased();

    void Jump();

    void StopJumping();

    void AddControllerYawInput(float Val) ;

    void AddControllerPitchInput(float Val) ;

    bool EnableTouchscreenMovement(UInputComponent* ThisInputComponent);
    
    class AProjectAwesomeCharacter* MyPawn;
    
};
