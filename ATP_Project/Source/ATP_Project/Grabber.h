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

	//attach physics and input handler, when play begin.
	virtual void _attach_physics_handler();
	virtual void _attach_input_handler();

	//Get Viewpoint Vector, and add to tickcomponent to get realtime view point
	virtual void get_view_point_vector(FVector &view_point_location, FRotator &view_point_rotation);
	//Get Object Reached (Hit)
	virtual void get_first_object_inreach(FHitResult &object_group_inreach, FVector &view_point_location, FRotator &view_point_rotation);

	//Grab for the first time, release for second time.
	virtual void _grab();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	bool is_grabbing = false;

	FVector view_point_location = FVector(0.f, 0.f, 0.f);

	FRotator view_point_rotation = FRotator(0.f, 0.f, 0.f);

	FHitResult object_group_inreach;

	UInputComponent *input_handler = nullptr;

	UPhysicsHandleComponent *physics_handler = nullptr;

	UPROPERTY(EditAnywhere)
	float length_reach = 500.f;

	UPROPERTY(EditAnywhere)
	float charactor_half_hight = 50.f;
};
