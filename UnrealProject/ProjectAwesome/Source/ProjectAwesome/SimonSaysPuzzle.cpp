// Fill out your copyright notice in the Description page of Project Settings.


#include "SimonSaysPuzzle.h"


#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASimonSaysPuzzle::ASimonSaysPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Board
	Board = CreateDefaultSubobject<UBoxComponent>(TEXT("Board"));
	Board->SetBoxExtent(FVector(350.0f, 350.0f, 350.0f));
	RootComponent = Board;
	Board->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Board->SetCollisionProfileName("OverlapAllDynamic");
	
	//Balls
	//Sphere Component
	RedSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RedSphereComponent"));
	RedSphereCollision->SetSphereRadius(10.0f);
	RedSphereCollision->SetupAttachment(RootComponent);
	RedSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RedSphereCollision->SetCollisionProfileName("BlockAllDynamic");

	//Mesh Component
	RedSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RedMesh"));
	RedSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RedSphere->SetCollisionProfileName("NoCollision");
	RedSphere->SetupAttachment(RedSphereCollision);

	//Sphere Component
	GreenSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("GreenSphereComponent"));
	GreenSphereCollision->SetSphereRadius(10.0f);
	GreenSphereCollision->SetupAttachment(RootComponent);
	GreenSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GreenSphereCollision->SetCollisionProfileName("BlockAllDynamic");

	//Mesh Component
	GreenSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GreenMesh"));
	GreenSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GreenSphere->SetCollisionProfileName("NoCollision");
	GreenSphere->SetupAttachment(GreenSphereCollision);
	
	//Sphere Component
	YellowSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BlueSphereComponent"));
	YellowSphereCollision->SetSphereRadius(10.0f);
	YellowSphereCollision->SetupAttachment(RootComponent);
	YellowSphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	YellowSphereCollision->SetCollisionProfileName("BlockAllDynamic");

	//Mesh Component
	YellowSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlueMesh"));
	YellowSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	YellowSphere->SetCollisionProfileName("NoCollision");
	YellowSphere->SetupAttachment(YellowSphereCollision);

}


void ASimonSaysPuzzle::SetAnswer()
{

	for (int i = 0; i < 6; i++)
	{
		m_PuzzleArray[i] = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	}

}

void ASimonSaysPuzzle::GetAnswer()
{
	for (int i = 0; i < 6; i++)
	{
		m_AnswerArray[i] = m_PuzzleArray[i];
	}
}

void ASimonSaysPuzzle::ResetPuzzle()
{
	SetAnswer();
	GetAnswer();
}

void ASimonSaysPuzzle::StartPuzzle()
{
	FTimerHandle SpawnTimer;
	auto& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(SpawnTimer, this, &ASimonSaysPuzzle::BlinkColor, 1, true);

	//Should blink the color in the array
	if (TimerManager.GetTimerRemaining(SpawnTimer) == 0)
	{
		BlinkColor();
	}
}

void ASimonSaysPuzzle::SetMaterialToMesh(UStaticMeshComponent* InMeshComp,
	const TArray<UMaterialInterface*>& InMaterials)
{
	if (InMeshComp != nullptr && InMaterials.Num() > 0)
	{
		for (int i = 0; i < InMaterials.Num(); i++)
		{
			UMaterialInterface* MaterialToAssign = InMaterials[i];
			if (MaterialToAssign != nullptr)
			{
				InMeshComp->SetMaterial(i, MaterialToAssign);
			}
		}
	}
}

void ASimonSaysPuzzle::BlinkColor()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_PuzzleArray[i] == 0)
		{
			
		}
		else if (m_PuzzleArray[i] == 1)
		{
			
		}
		else if (m_PuzzleArray[i] == 2)
		{
			
		}
	}
}

// Called when the game starts or when spawned
void ASimonSaysPuzzle::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SpawnTimer;
	auto& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(SpawnTimer, this, &ASimonSaysPuzzle::BlinkColor, 1, true);
}

// Called every frame
void ASimonSaysPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

