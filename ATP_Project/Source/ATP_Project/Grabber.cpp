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
	UE_LOG(LogTemp, Error, TEXT("%s Get Physics Handle Component ~!"), *(GetOwner()->GetName()));
	}
	else
	{
		//	Debug:
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component ~!"), *(GetOwner()->GetName()));
	}

	//	Look for attached Input handler
	//	**** Bind Action
	input_handler = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input_handler)
	{
		//Debug:
		UE_LOG(LogTemp, Warning, TEXT("%s Input Handle Component is found~!"), *(GetOwner()->GetName()));

		//****		Bind an Action to Grabber
		//****		Grab when E Pressed first time
		//****		Release when E pressed second time
		input_handler->BindAction("Grab", IE_Pressed, this, &UGrabber::_grab);
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
	get_tpc_reach_vector(line_start, line_end, view_point_location, view_point_rotation);
	get_reachable_object(line_start, line_end);
};

// Get player view point
//is being used by get_tpc_reach_vector()
void UGrabber::get_viewpoint_vector(FVector &location, FRotator &rotation)
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT location,
		OUT rotation);
	//Debug:
	// UE_LOG(LogTemp, Warning, TEXT("Location : %s , Rotation : %s"), *view_point_location.ToString(), *view_point_rotation.ToString());
}

//Get Third Person Charactor Reachable Vector
//get_viewpoint_vector(FVector &view_point_location, FRotator &view_point_rotation) is used.
void UGrabber::get_tpc_reach_vector(FVector &start, FVector &end, FVector &location, FRotator &rotation)
{
	get_viewpoint_vector(location, rotation);
	// Line Start Point (FVector)  ---------get Charactor location for ThirdPersonMode
	// line_start ---------- A little Higher to reach head
	start = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, charactor_half_hight);

	//Line End Point (FVector)  ----------create by view point and reachable distance
	//line_end    -----------Reachable distance
	end = location + rotation.Vector() * length_reach;
}

//get_reachable_object : Should return an Actor reference
void UGrabber::get_reachable_object(FVector &start, FVector &end)
{
	//Draw A Debug Line
	DrawDebugLine(
		GetWorld(),
		start,
		end,
		FColor::Blue,
		false,
		0.f,
		0.f,
		10.f);

	//setup queryparams
	FCollisionQueryParams ignore_prama{FName(TEXT("")), false, GetOwner()};

	//Hit Object
	FHitResult object_hitting;
	GetWorld()->LineTraceSingleByObjectType(
		OUT object_hitting,
		line_start,
		line_end,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		ignore_prama);
	//Get hit actor
	AActor *actor_hit = object_hitting.GetActor();

	//Debug:
	if (actor_hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *(actor_hit->GetName()));
	}
}

//Grab FUNCTION: _grab
void UGrabber::_grab()
{
	if (is_grabbing == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Released ~!"));
		is_grabbing = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab something ~!"));
		is_grabbing = true;
	}
}
