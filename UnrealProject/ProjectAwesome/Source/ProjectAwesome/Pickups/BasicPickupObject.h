// Fill out your copyright notice in the Description page of Project Settings.
//Author: Brandon Coates
//Date Modified : 3 / 14 / 2021
//Comment / Description : Base Pickup for all objects
//ChangeLog :
//3 / 14 / 2021 : Created Basic Pick Up Functions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicPickupObject.generated.h"

UCLASS()
class PROJECTAWESOME_API ABasicPickupObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicPickupObject();
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void Disable();

	UFUNCTION()
		virtual void Enable();

	bool bCanBeDropped;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BasicPickup_Mesh;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void DestroyObject();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions to attach and detach objects from player
	void Attach(USkeletalMeshComponent* HoldingComponent);
	void Detach(FVector direction);

};
