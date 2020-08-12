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
	if (!physics_handler)
	{
		return;
	}
	if (physics_handler->GrabbedComponent)
	{
		physics_handler->SetTargetLocation(get_reach_vector_end());
	}
};

//---------------------------------------------------------------------------------------------------Yumoo
//Attach physics handler
void UGrabber::_attach_physics_handler()
{
	physics_handler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physics_handler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component ~!"), *(GetOwner()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Physics Handle Component is Attached~!"), *(GetOwner()->GetName()));
	}
}
//Attach input handler
void UGrabber::_attach_input_handler()
{
	//	Look for attached Input handler
	//	**** Bind Action
	input_handler = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input_handler == nullptr)
	{
		//	Debug:
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Handle Component ~!"), *(GetOwner()->GetName()));
	}
	else
	{
		// Debug:
		UE_LOG(LogTemp, Warning, TEXT("%s Input Handle Component is found~!"), *(GetOwner()->GetName()));
		//****		Bind an Action to Grabber
		input_handler->BindAction("Grab", IE_Pressed, this, &UGrabber::_grab);
	}
}

//get_first_object_inreach and return a group of actors in reach :: in here should be only one object
FHitResult UGrabber::get_first_object_inreach()
{
	FHitResult object_group_inreach;
	//setup queryparams
	FCollisionQueryParams ignore_prama{FName(TEXT("")), false, GetOwner()};

	//Object In Reach
	GetWorld()->LineTraceSingleByObjectType(
		OUT object_group_inreach,
		//**** start vector	:	ThirdPersonCharactor + half_hight(raise handle start point a little higher)
		get_reach_vector_start(),
		//**** end vector	:	view point location + rotation direction * length(distance in reach)
		get_reach_vector_end(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		ignore_prama);

	return object_group_inreach;
	//Debug:
	// if (object_group_inreach.GetActor())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *(object_group_inreach.GetActor()->GetName()));

	// }
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
		FHitResult object_group_inreach = get_first_object_inreach();
		if (object_group_inreach.GetActor())
		{
			if (!physics_handler)
			{
				return;
			}

			physics_handler->GrabComponentAtLocationWithRotation(
				object_group_inreach.GetComponent(), //Which component we grab at.
				NAME_None,
				get_reach_vector_end(), //when grab, hold to which location
				GetOwner()->GetActorRotation());

			is_grabbing = true;
		}
	}
}

FVector UGrabber::get_reach_vector_start()
{
	return GetOwner()->GetActorLocation() + FVector(0.f, 0.f, charactor_half_hight);
}

FVector UGrabber::get_reach_vector_end()
{
	FVector view_point_location;
	FRotator view_point_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT view_point_location,
		OUT view_point_rotation);
	return view_point_location + view_point_rotation.Vector() * length_reach;
}