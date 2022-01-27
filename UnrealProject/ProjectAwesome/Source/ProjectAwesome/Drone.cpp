// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"

#include "Components/BoxComponent.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Empty();
	Tags.Add("AIDrone");

    DroneBox = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    DroneBox->SetBoxExtent(FVector(2, 2, 2));
    DroneBox->BodyInstance.SetCollisionProfileName("BlockAll");
    DroneBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    DroneBox->SetEnableGravity(false);
    SetRootComponent(DroneBox);

    DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    DroneMesh->SetSimulatePhysics(false);
    DroneMesh->SetCollisionProfileName("NoCollision");
    DroneMesh->SetupAttachment(RootComponent);
    DroneMesh->SetRelativeScale3D(FVector(1.0f));

}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();

    if (bPatrol == true)
    {
        //CALL MoveToNextPatrolPoint()
        MoveToNextPatrolPoint();
    }
}

void ADrone::MoveToNextPatrolPoint()
{
    if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
    {
        CurrentPatrolPoint = FirstPatrolPoint;

    }
    else
    {
        CurrentPatrolPoint = SecondPatrolPoint;
    }

    FVector Direction = (GetActorLocation() - CurrentPatrolPoint->GetActorLocation());
    Direction.Normalize();

    FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
    NewLookAt.Pitch = 0;
    NewLookAt.Roll = 0;
    NewLookAt.Yaw += -180;

    SetActorRotation(NewLookAt);
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //COMMENT: Patrol Goal Checks
    //IF CurrentPatrolPoint IS NOT nullptr
    if (CurrentPatrolPoint != nullptr)
    {
        FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
        float DistanceToGoal = Delta.Size();

        //COMMENT Check if we are within 50 
        if (DistanceToGoal < 50)
        {
            MoveToNextPatrolPoint();
        }

        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 600.f));
    }
}

