// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//get player
	actor_accept = GetWorld()->GetFirstPlayerController()->GetPawn();

	//get owner
	this_owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (trigger_volume->IsOverlappingActor(actor_accept))
	{
		_open_door();
		close_time = GetWorld()->GetTimeSeconds();
		close_time =close_time + close_delay;
		
	}
	if(close_time <= GetWorld()->GetTimeSeconds()){
		_close_door();
	}
}

//function : _open_door()    open the door
void UOpenDoor::_open_door()
{
	this_owner->SetActorRotation(FRotator(0.f, open_angle, 0.f));
}

void UOpenDoor::_close_door()
{
	this_owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}
