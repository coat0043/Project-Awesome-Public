// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Tags.Empty();
    Tags.Add("AIRocket");

    MissileBox = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    MissileBox->SetBoxExtent(FVector(2, 2, 2));
    MissileBox->BodyInstance.SetCollisionProfileName("BlockAll");
    MissileBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    MissileBox->SetEnableGravity(false);
    SetRootComponent(MissileBox);

    MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    MissileMesh->SetSimulatePhysics(false);
    MissileMesh->SetCollisionProfileName("NoCollision");
    MissileMesh->SetupAttachment(RootComponent);
    MissileMesh->SetRelativeScale3D(FVector(1.0f));

    MissileMovement = CreateDefaultSubobject<UMovementComponent>("MovementComponent");

}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector target (GetActorLocation().X, GetActorLocation().Y,10000);

    if (m_IsLaunched == true)
    {
        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), target, DeltaTime, 800.f));
    }
}

void AMissile::Launch(float value)
{
    //if (!AudioComponent->IsPlaying()) {
	//AudioComponent->SetSound(ImpactSound);
    //AudioComponent->Play();
	
    m_IsLaunched = true;
    //UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), MissileSound, GetActorLocation());

}

