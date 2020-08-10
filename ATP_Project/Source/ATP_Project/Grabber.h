// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATP_PROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float length_reach = 520.f;

	UPROPERTY(EditAnywhere)
	float charactor_half_hight = 70.f;

	UInputComponent *input_handler = nullptr;

	UPhysicsHandleComponent *physics_handler = nullptr;

	bool is_grabbing = false;

	//Get Reach Vector
	virtual FVector get_reach_vector_start();
	virtual FVector get_reach_vector_end();

	//attach physics and input handler, when play begin.
	virtual void _attach_physics_handler();
	virtual void _attach_input_handler();

	//Get Object Reached (Hit)
	virtual FHitResult get_first_object_inreach();

	//Grab for the first time, release for second time.
	virtual void _grab();
};
