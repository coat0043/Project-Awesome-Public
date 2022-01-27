// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPickupObject.h"
#include "../ProjectAwesomeCharacter.h"
#include <Components/SphereComponent.h>
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasicPickupObject::ABasicPickupObject() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bCanBeDropped = true;

	//Sphere Component
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollision->SetSphereRadius(24.f);
	RootComponent = SphereCollision;
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionProfileName("BlockAllDynamic");
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	//Mesh Component

	BasicPickup_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BasicPickup_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BasicPickup_Mesh->SetCollisionProfileName("NoCollision");

	BasicPickup_Mesh->SetupAttachment(RootComponent);

	Tags.Add("Pickup");
}

// Called when the game starts or when spawned
void ABasicPickupObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicPickupObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicPickupObject::Attach(USkeletalMeshComponent* HoldingComponent)
{
	if (HoldingComponent)
	{
		//DISABLE Physics
		SphereCollision->SetSimulatePhysics(false);

		SphereCollision->SetNotifyRigidBodyCollision(false);

		SphereCollision->AttachToComponent(HoldingComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Muzzle"));

	}
}

void ABasicPickupObject::Detach(FVector direction)
{
	//Enable Sphysics
	SphereCollision->SetSimulatePhysics(true);

	SphereCollision->SetNotifyRigidBodyCollision(true);

	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	SphereCollision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	
	SphereCollision->GetBodyInstance()->AddForce(direction * 500 * SphereCollision->GetMass());

}

void ABasicPickupObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ABasicPickupObject::DestroyObject()
{
	Destroy();
}

void ABasicPickupObject::Enable()
{
	if (BasicPickup_Mesh)
	{
		this->SetActorHiddenInGame(false);
		SphereCollision->SetActive(true);

		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ABasicPickupObject::Disable()
{
	if (BasicPickup_Mesh)
	{
		this->SetActorHiddenInGame(true);
		SphereCollision->SetActive(false);

		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABasicPickupObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
