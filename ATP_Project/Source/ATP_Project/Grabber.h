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

	//Get Facing Vector
	//no return for now
	virtual void get_viewpoint_vector(FVector &view_point_location, FRotator &view_point_rotation);
	virtual void get_tpc_reach_vector(FVector &line_start, FVector &line_end, FVector &view_point_location, FRotator &view_point_rotation);
	virtual void get_reachable_object(FVector &line_start, FVector &line_end);
	//Grab what's in reach vector
	//Grab for the first time, release for second time.
	virtual void _grab();




public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	bool is_grabbing = false;

	FVector view_point_location = FVector(0.f, 0.f, 0.f);
	
	FRotator view_point_rotation = FRotator(0.f, 0.f, 0.f);

	FVector line_start = FVector(0.f, 0.f, 0.f);

	FVector line_end = FVector(0.f, 0.f, 0.f);

	UInputComponent *input_handler = nullptr;

	UPhysicsHandleComponent *physics_handler = nullptr;

	UPROPERTY(EditAnywhere)
	float length_reach = 500.f;

	UPROPERTY(EditAnywhere)
	float charactor_half_hight = 50.f;

};
