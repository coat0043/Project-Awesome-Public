// Fill out your copyright notice in the Description page of Project Settings.

/*Author: Brandon Coates
Date Modified : 4 / 09 / 2021
Comment / Description : Missile Object
ChangeLog :
4 / 09 / 2021 : Missile Movement / Launch Function added
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class PROJECTAWESOME_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

	UPROPERTY(Category = Missile, VisibleAnywhere, meta = (AllowPrivateAccess))
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
		class USoundBase* MissileSound;

	UPROPERTY(EditDefaultsOnly, Category = "MissileActor")
		class UStaticMeshComponent* MissileMesh;

	UPROPERTY(VisibleAnywhere, Category = "MissileActor")
		class UBoxComponent* MissileBox;

	UPROPERTY(EditDefaultsOnly, Category = "MissileActor")
		class UParticleSystem* MissileTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "MissileActor")
		class UMovementComponent* MissileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool m_IsLaunched = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch(float value);

};
