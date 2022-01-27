// Fill out your copyright notice in the Description page of Project Settings.


#include "OutOfBoundsWall.h"
#include "Components/BoxComponent.h"

// Sets default values
AOutOfBoundsWall::AOutOfBoundsWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetBoxExtent(FVector(2000.0f, 2000.0f, 2000.0f));
	BoxCollision->SetSimulatePhysics(false);
	BoxCollision->SetCollisionProfileName("OverLapOnlyPawn");
	SetRootComponent(BoxCollision);

	CountdownTime = 5.0f;
	Timer = 0.0f;
	Message = "Its dangerous out there go back at once ";
	bIsTimerRunning = false;

	Tags.Add("OutOfBounds");
}

// Called when the game starts or when spawned
void AOutOfBoundsWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOutOfBoundsWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTimerRunning)
	{
		Timer += DeltaTime;
	}
}

void AOutOfBoundsWall::StartTimer()
{
	bIsTimerRunning = true;
}

void AOutOfBoundsWall::ResetTimer()
{
	Timer = 0.0f;
	bIsTimerRunning = false;
}