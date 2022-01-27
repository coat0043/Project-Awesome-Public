// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KeyItemPickup.h"
#include "../GlobalDataForProject.h"

#include "AudioRecordingKeyItem.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTAWESOME_API AAudioRecordingKeyItem : public AKeyItemPickup
{
	GENERATED_BODY()
public:
	AAudioRecordingKeyItem();

	void PlayAudio();

	void OnPickUp();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	    class UAudioComponent* RecordingAudioComponent;

	//Enum for keyitems
	KeyItemTypes Type;
};
