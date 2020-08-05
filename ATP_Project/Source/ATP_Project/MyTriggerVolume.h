// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "MyTriggerVolume.generated.h"

/**
 *
 */
UCLASS()
class ATP_PROJECT_API AMyTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AMyTriggerVolume();

	// UFUNCTION()
	// 	void OverlapBegin(class AActor* overlapped_actor, class AActor* other_actor);

	// UFUNCTION()
	// 	void OverlapEnd(class AActor* overlapped_actor, class AActor* other_actor);
};
