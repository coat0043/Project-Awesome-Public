// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OutOfBoundsWall.generated.h"

UCLASS()
class PROJECTAWESOME_API AOutOfBoundsWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutOfBoundsWall();

	float CountdownTime;
	float Timer;
	FString Message;
	bool bIsTimerRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
		class UBoxComponent* BoxCollision;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void StartTimer();
	void ResetTimer();
};
