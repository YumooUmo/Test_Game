// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("A Grabber start ~!"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//...
	facing_vector();
};

void UGrabber::facing_vector(){
		// Get player view point this tick
	FVector view_point_location;
	FRotator view_point_rotation;

	// Charactor location for ThirdPersonMode
	// A little Higher to reach head
	FVector charactor_location = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, charactor_half_hight);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT view_point_location,
		OUT view_point_rotation);
	//Log_out for test
	// UE_LOG(LogTemp, Warning, TEXT("Location : %s , Rotation : %s"), *view_point_location.ToString(), *view_point_rotation.ToString());

	//Reachable distance
	FVector line_debug = view_point_location + view_point_rotation.Vector() * length_reach;
	DrawDebugLine(
		GetWorld(),
		charactor_location,
		line_debug,
		FColor::Blue,
		false,
		0.f,
		0.f,
		10.f);
	//See what we hit
}