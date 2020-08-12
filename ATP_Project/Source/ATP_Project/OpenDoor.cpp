// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#define OUT

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

	//Debug : if trigger_volume is nullptr;
	if (!trigger_volume)
	{
		UE_LOG(LogTemp, Error, TEXT("Trigger_Volume is missing ~!"));
		return;
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//If total mass on trigger_volume is more than 50kg, then open the door
	if (!trigger_volume)
	{
		return;
	}
	if (get_total_mass() >= mass_open)
	{
		_open_door();
	}
	else
	{
		_close_door();
	};

	// UE_LOG(LogTemp, Error, TEXT(" Total Mass is %s ~!"), get_total_mass());
	// debug();
}

//function : _open_door()    open the door
void UOpenDoor::_open_door()
{
	if (open_status == false)
	{
		open_status = true;
		OnOpen.Broadcast();
	}
}

void UOpenDoor::_close_door()
{
	if (open_status)
	{
		open_status = false;
		OnClose.Broadcast();
	}
}
//Get Total Mass Of Actors on Trigger_volume Bounds to this Door;
float UOpenDoor::get_total_mass()
{
	float total_mass = 0.f;
	TArray<AActor *> actors_overlapping;

	trigger_volume->GetOverlappingActors(OUT actors_overlapping);
	for (const auto &actor : actors_overlapping)
	{
		total_mass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Error, TEXT(" Total Mass is %s ~!"), *FString::SanitizeFloat(total_mass));
	return total_mass;
}

//debug
void UOpenDoor::debug()
{
	TArray<AActor *> actors_overlapping;
	trigger_volume->GetOverlappingActors(OUT actors_overlapping);
	for (const auto &actor : actors_overlapping)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on the plate ~!"), *actor->GetName());
	}
}