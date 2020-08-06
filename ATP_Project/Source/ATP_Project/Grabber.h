// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATP_PROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Get Facing Vector
	//no return for now
	virtual void _reach_facing_vector();

	//Grab what's in reach vector
	virtual void _grab();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float length_reach = 500.f;

	UPROPERTY(EditAnywhere)
	float charactor_half_hight = 50.f;

	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* physics_handler = nullptr;

	UPROPERTY(VisibleAnywhere)
	UInputComponent* input_handler = nullptr;
};
