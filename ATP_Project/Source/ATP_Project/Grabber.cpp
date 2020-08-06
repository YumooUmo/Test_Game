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
	_attach_physics_handler();
	_attach_input_handler();
}

//	Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//...

	//after grabb, keep grabbed component in the right place
	if (physics_handler->GrabbedComponent)
	{
		get_view_point_vector(view_point_location, view_point_rotation);
		physics_handler->SetTargetLocation((view_point_location + view_point_rotation.Vector() * length_reach));
	}
};

//---------------------------------------------------------------------------------------------------Yumoo
//Attach physics handler
void UGrabber::_attach_physics_handler()
{
	physics_handler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physics_handler)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Get Physics Handle Component ~!"), *(GetOwner()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component ~!"), *(GetOwner()->GetName()));
	}
}
//Attach input handler
void UGrabber::_attach_input_handler()
{
	//	Look for attached Input handler
	//	**** Bind Action
	input_handler = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input_handler)
	{
		// Debug:
		UE_LOG(LogTemp, Warning, TEXT("%s Input Handle Component is found~!"), *(GetOwner()->GetName()));
		//****		Bind an Action to Grabber
		input_handler->BindAction("Grab", IE_Pressed, this, &UGrabber::_grab);
	}
	else
	{
		//	Debug:
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Handle Component ~!"), *(GetOwner()->GetName()));
	}
}

// Get player view point
void UGrabber::get_view_point_vector(FVector &location, FRotator &rotation)
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT location,
		OUT rotation);
	//Debug:
	// UE_LOG(LogTemp, Warning, TEXT("Location : %s , Rotation : %s"), *view_point_location.ToString(), *view_point_rotation.ToString());
}

//get_first_object_inreach and return a group of actors in reach :: in here should be only one object
void UGrabber::get_first_object_inreach(FHitResult &group_inreach, FVector &location, FRotator &rotation)
{
	//
	get_view_point_vector(location, rotation);
	//setup queryparams
	FCollisionQueryParams ignore_prama{FName(TEXT("")), false, GetOwner()};

	//Object In Reach
	GetWorld()->LineTraceSingleByObjectType(
		OUT group_inreach,
		//**** start vector	:	ThirdPersonCharactor + half_hight(raise handle start point a little higher)
		GetOwner()->GetActorLocation() + FVector(0.f, 0.f, charactor_half_hight),
		//**** end vector	:	view point location + rotation direction * length(distance in reach)
		location + rotation.Vector() * length_reach,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		ignore_prama);

	//Debug:
	if (group_inreach.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *(group_inreach.GetActor()->GetName()));
	}
}

//Grab FUNCTION: _grab
//****		Grab when E Pressed first time
//****		Release when E pressed second time
void UGrabber::_grab()
{
	if (is_grabbing == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Released ~!"));
		is_grabbing = false;
		physics_handler->ReleaseComponent();
	}
	else
	{
		//get first object in reach
		get_first_object_inreach(object_group_inreach, view_point_location, view_point_rotation);
		if (object_group_inreach.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Grab something ~!"));
			is_grabbing = true;
			physics_handler->GrabComponent(
				object_group_inreach.GetComponent(), //Which component we grab at.
				NAME_None,
				view_point_location + view_point_rotation.Vector() * length_reach, //when grab, hold to which location
				true);
		}
	}
}
