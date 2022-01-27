// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAwesomeCharacter.h"

#include "DrawDebugHelpers.h"
#include "ProjectAwesomeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Pickups/BasicPickupObject.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "ProjectAwesomeGameMode.h"
#include "CustomPlayerController.h"
#include "OutOfBoundsWall.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AProjectAwesomeCharacter
//This is a Test Comment to see if it will properly push to git hub

AProjectAwesomeCharacter::AProjectAwesomeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Trigger"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->SetCollisionProfileName("OverlapAll");
	SphereComponent->SetGenerateOverlapEvents(true);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectAwesomeCharacter::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectAwesomeCharacter::OnOverlapEnd);
	

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(Mesh1P, TEXT("LeftHandGrip"));
	FP_Gun->SetupAttachment(RootComponent);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);


}

void AProjectAwesomeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("LeftHandGrip"));

	SpawnPoint = GetActorLocation();

}

void AProjectAwesomeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (OverLappedWall != nullptr)
	{

		if (OverLappedWall->Timer > OverLappedWall->CountdownTime)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Respawn at Base"));
			this->SetActorLocation(SpawnPoint);
			OverLappedWall->ResetTimer();
			
		}
		
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

USkeletalMeshComponent* AProjectAwesomeCharacter::GetSkeletalMesh()
{
	return Mesh1P;
}

void AProjectAwesomeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 //Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjectAwesomeCharacter::OnResetVR);

	//Raycast Controls
	PlayerInputComponent->BindAction("RaycastPressed", IE_Pressed, this, &AProjectAwesomeCharacter::RaycastPressed);
	PlayerInputComponent->BindAction("RaycastPressed", IE_Released, this, &AProjectAwesomeCharacter::RaycastReleased);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectAwesomeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectAwesomeCharacter::MoveRight);

	//// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	//// "turn" handles devices that provide an absolute delta, such as a mouse.
	//// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AProjectAwesomeCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectAwesomeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AProjectAwesomeCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectAwesomeCharacter::LookUpAtRate);
}

void AProjectAwesomeCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProjectAwesomeCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	//if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	//{
	//	OnFire();
	//}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AProjectAwesomeCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}


void AProjectAwesomeCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AProjectAwesomeCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AProjectAwesomeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	APawn::AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjectAwesomeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	APawn::AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProjectAwesomeCharacter::SetupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace)
{
	FVector CamLoc;
	FRotator CamRot;

	Controller->GetPlayerViewPoint(CamLoc, CamRot); // Get the camera position and rotation

	StartTrace = CamLoc; // trace start is the camera location
	Direction = CamRot.Vector();
	EndTrace = StartTrace + Direction * 500;
}

AActor* AProjectAwesomeCharacter::RayCastGetActor()
{
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller because we don't want bots to grab the use object and we need a controller for the GetPlayerViewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		//World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, ObjectTypeQuery1, TraceParams); // simple trace function  ECC_PhysicsBody
		World->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_PhysicsBody, TraceParams); // simple trace function  ECC_PhysicsBody
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1.f);
		return Hit.GetActor();
	}
	return nullptr;
}

void AProjectAwesomeCharacter::RaycastPressed()
{
	//Ray Cast to check if a Actor is hit by a raycast
	AActor* PickedActor = RayCastGetActor();
	if (PickedActor)
	{
		ABasicPickupObject* item = Cast<ABasicPickupObject>(PickedActor);
		if (item)
		{
			CurrentItem = item;
			item->Attach(FP_Gun);
		}
	}
}

void AProjectAwesomeCharacter::RaycastReleased()
{
	if (CurrentItem)
	{
		CurrentItem->Detach(FirstPersonCameraComponent->GetForwardVector());
		CurrentItem = nullptr;
	}
}

void AProjectAwesomeCharacter::AddControllerYawInput(float Val)
{
	APawn::AddControllerYawInput(Val);
	
}

void AProjectAwesomeCharacter::AddControllerPitchInput(float Val)
{
	APawn::AddControllerPitchInput(Val);
	
	
	
}

bool AProjectAwesomeCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProjectAwesomeCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AProjectAwesomeCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AProjectAwesomeCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

void AProjectAwesomeCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
										 const FHitResult& SweepResult)
{
	if (OtherActor != NULL)
	{
		
		if (OtherActor->ActorHasTag("OutOfBounds"))
		{
			
			if (Cast<AOutOfBoundsWall>(OtherActor) != NULL)
			{
			
				OverLappedWall = Cast<AOutOfBoundsWall>(OtherActor);

				if (OverLappedWall->bIsTimerRunning == false)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OverLapping OoBs wall!"));
					OverLappedWall->StartTimer();
				}
				
			}

		}
	
	
	}
}

void AProjectAwesomeCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != NULL)
	{

		if (OtherActor->ActorHasTag("OutOfBounds"))
		{

			if (Cast<AOutOfBoundsWall>(OtherActor) != NULL)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Overlab Wall"));
				OverLappedWall->ResetTimer();
				
			}
		}
	}
}
