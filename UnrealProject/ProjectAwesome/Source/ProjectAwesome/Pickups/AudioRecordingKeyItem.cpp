// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioRecordingKeyItem.h"
#include "Components/AudioComponent.h"
#include "../ProjectAwesomeGameMode.h"

AAudioRecordingKeyItem::AAudioRecordingKeyItem()
{
    
    Type = KeyItemTypes::Recording;

    RecordingAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("RecordingAudio"));
    RecordingAudioComponent->bAutoActivate = false;
    RecordingAudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    RecordingAudioComponent->SetupAttachment(RootComponent);

   
}

void AAudioRecordingKeyItem::PlayAudio()
{
    RecordingAudioComponent->Play();
}

void AAudioRecordingKeyItem::OnPickUp()
{
    AProjectAwesomeGameMode* GMode = Cast<AProjectAwesomeGameMode>(GetWorld()->GetAuthGameMode());
    GMode->bIsRecordingPickedUp = true;
    Disable();
    
}

