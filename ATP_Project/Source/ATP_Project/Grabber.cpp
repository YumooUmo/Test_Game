// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initia lized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

//	Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("A Grabber start ~!"));

	
	//	Look for attached Physics handler
	physics_handler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physics_handler)
	{
	}
	else
	{
		//	Debug:
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component ~!"), *(GetOwner()->GetName()));
	}

	//	Look for attached Input handler
	input_handler = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input_handler)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Input Handle Component is found~!"), *(GetOwner()->GetName()));
		input_handler->BindAction("Grab",IE_Pressed,this,&UGrabber::_grab);
	}
	else
	{
		//	Debug:
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Handle Component ~!"), *(GetOwner()->GetName()));
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//...
	_reach_facing_vector();
};

void UGrabber::_reach_facing_vector()
{
	// Get player view point this tick
	FVector view_point_location;
	FRotator view_point_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT view_point_location,
		OUT view_point_rotation);

	// Charactor location for ThirdPersonMode
	// A little Higher to reach head
	FVector line_start = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, charactor_half_hight);

	//Log_out for test
	// UE_LOG(LogTemp, Warning, TEXT("Location : %s , Rotation : %s"), *view_point_location.ToString(), *view_point_rotation.ToString());

	//Reachable distance
	FVector line_end = view_point_location + view_point_rotation.Vector() * length_reach;

	//Draw A Debug Line
	DrawDebugLine(
		GetWorld(),
		line_start,
		line_end,
		FColor::Blue,
		false,
		0.f,
		0.f,
		10.f);
	//setup queryparams
	FCollisionQueryParams ignore_prama{FName(TEXT("")), false, GetOwner()};

	//See what we hit
	FHitResult object_hitting;
	GetWorld()->LineTraceSingleByObjectType(
		OUT object_hitting,
		line_start,
		line_end,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		ignore_prama);
	//get hit actor
	AActor *actor_hit = object_hitting.GetActor();
	if (actor_hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *(actor_hit->GetName()));
	}

	//handle
};

void UGrabber::_grab(){
	UE_LOG(LogTemp, Error, TEXT("Grab Pressed"));
}