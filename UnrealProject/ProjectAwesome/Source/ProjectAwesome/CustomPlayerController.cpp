// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "ProjectAwesomeCharacter.h"
#include "ProjectAwesomeGameMode.h"



void ACustomPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    MyPawn = Cast<AProjectAwesomeCharacter>(aPawn);
    
    
    
}

void ACustomPlayerController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());
    

    Super::OnUnPossess();
}

void ACustomPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    // set up gameplay key bindings
    

        if (InputComponent != nullptr) {
            // Bind jump events
            InputComponent->BindAction("Jump", IE_Pressed, this, &ACustomPlayerController::Jump);
            InputComponent->BindAction("Jump", IE_Released, this, &ACustomPlayerController::StopJumping);



            InputComponent->BindAction("ResetVR", IE_Pressed, this, &ACustomPlayerController::OnResetVR);

            //Raycast Controls
            InputComponent->BindAction("RaycastPressed", IE_Pressed, this, &ACustomPlayerController::RaycastPressed);
            InputComponent->BindAction("RaycastPressed", IE_Released, this, &ACustomPlayerController::RaycastReleased);

            // Bind movement events
            InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::MoveForward);
            InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::MoveRight);

            // We have 2 versions of the rotation bindings to handle different kinds of devices differently
            // "turn" handles devices that provide an absolute delta, such as a mouse.
            // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
            
            InputComponent->BindAxis("Turn", this, &ACustomPlayerController::AddControllerYawInput);
            InputComponent->BindAxis("TurnRate", this, &ACustomPlayerController::TurnAtRate);
            InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::AddControllerPitchInput);
            InputComponent->BindAxis("LookUpRate", this, &ACustomPlayerController::LookUpAtRate);

            // Enable touchscreen input
            EnableTouchscreenMovement(InputComponent);

        }
    
}

void ACustomPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{

}

void ACustomPlayerController::OnResetVR()
{
    if (MyPawn) 
    {
        MyPawn->OnResetVR();
    }
}

void ACustomPlayerController::MoveForward(float Val)
{
    if (MyPawn)
    {
        MyPawn->MoveForward(Val);
    }
}

void ACustomPlayerController::MoveRight(float Val)
{
    if (MyPawn)
    {
        MyPawn->MoveRight(Val);
    }
}

void ACustomPlayerController::TurnAtRate(float Val)
{
    if (MyPawn)
    {
        MyPawn->TurnAtRate(Val);
    }
}

void ACustomPlayerController::LookUpAtRate(float Val)
{
    if (MyPawn)
    {
        MyPawn->LookUpAtRate(Val);
    }
}

void ACustomPlayerController::RaycastPressed()
{
    if (MyPawn)
    {
        MyPawn->RaycastPressed();
    }
}

void ACustomPlayerController::RaycastReleased() 
{
    if (MyPawn)
    {
        MyPawn->RaycastReleased();
    }
}

void ACustomPlayerController::Jump()
{
    if (MyPawn)
    {
        MyPawn->Jump();
    }
}

void ACustomPlayerController::StopJumping()
{
    if (MyPawn)
    {
        MyPawn->StopJumping();
    }
}

void ACustomPlayerController::AddControllerYawInput(float Val)
{
    
    if (MyPawn)
    {
        MyPawn->AddControllerYawInput(Val);
        
    }
   
}

void ACustomPlayerController::AddControllerPitchInput(float Val)
{
    if (MyPawn)
    {
        MyPawn->AddControllerPitchInput(Val);
        
    }
    
    
}


bool ACustomPlayerController::EnableTouchscreenMovement(UInputComponent* ThisInputComponent)
{
    if (MyPawn)
    {
       return MyPawn->EnableTouchscreenMovement(ThisInputComponent);
    }

    return false;
}