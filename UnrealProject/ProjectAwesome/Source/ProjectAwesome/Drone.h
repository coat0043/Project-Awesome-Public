// Fill out your copyright notice in the Description page of Project Settings.
//Author: Brandon Coates
//Date Modified : 2 / 14 / 2021
//Comment / Description : Drone Object for special event
//ChangeLog :
//2 / 14 / 2021 : Created Drone Class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drone.generated.h"

UCLASS()
class PROJECTAWESOME_API ADrone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrone();

    /*The Characters capsule component, handles collision and is the root component*/
    UPROPERTY(Category = Drone, VisibleAnywhere, meta = (AllowPrivateAccess))
        class UCapsuleComponent* CapsuleComponent;

    UPROPERTY(EditAnywhere, Category = "Effects")
        class USoundBase* DroneSound;

    UPROPERTY(EditDefaultsOnly, Category = "DroneActor")
        class UStaticMeshComponent* DroneMesh;

    UPROPERTY(VisibleAnywhere, Category = "DroneActor")
        class UBoxComponent* DroneBox;


    // This drone actor uses two patrol points to move.
    // TODO: Despawn object when out of sight 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    /* Let the guard go on patrol */
    UPROPERTY(EditInstanceOnly, Category = "AI")
        bool bPatrol;

    /* First of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* FirstPatrolPoint;

    /* Second of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* SecondPatrolPoint;

    // The current point the actor is either moving to or standing at
    AActor* CurrentPatrolPoint;

    UFUNCTION() //WIthout this, the function will be inlined and optimized out
        void MoveToNextPatrolPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
