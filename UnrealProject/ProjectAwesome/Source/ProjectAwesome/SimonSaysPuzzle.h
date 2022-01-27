// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimonSaysPuzzle.generated.h"

UCLASS()
class PROJECTAWESOME_API ASimonSaysPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimonSaysPuzzle();

	void SetAnswer();
	void GetAnswer();
	void ResetPuzzle();
	void StartPuzzle();
	void SetMaterialToMesh(UStaticMeshComponent* InMeshComp, const TArray<UMaterialInterface*>& InMaterials);
	void BlinkColor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Board
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
		class UBoxComponent* Board;

	//Balls
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
		class USphereComponent* RedSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* RedSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
		class USphereComponent* GreenSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GreenSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
		class USphereComponent* YellowSphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* YellowSphere;

	bool m_IsSolved = false;
	
	int m_PuzzleArray[6] = {};
	
	int m_AnswerArray[6] = {};
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
