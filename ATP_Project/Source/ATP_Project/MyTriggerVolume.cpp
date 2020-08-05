#include "MyTriggerVolume.h"

AMyTriggerVolume::AMyTriggerVolume()
{
	// OnActorBeginOverlap.AddDynamic(this, &AMyTriggerVolume::OverlapBegin);
	// OnActorEndOverlap.AddDynamic(this, &AMyTriggerVolume::OverlapBegin);
}

void AMyTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}


// void AMyTriggerVolume::OverlapBegin(class AActor* overlapped_actor, class AActor* OtherActor)
// {
// 	if (OtherActor && (OtherActor != this))
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin !"))
// 			UE_LOG(LogTemp, Warning, TEXT("Overlap Actor is %s"), *overlapped_actor->GetName());
// 	}
// }

// void AMyTriggerVolume::OverlapEnd(class AActor* overlapped_actor, class AActor* other_actor)
// {
// 	if (other_actor && (other_actor != this))
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Overlap Ended !"))
// 			UE_LOG(LogTemp, Warning, TEXT("Overlap Actor is %s"), *other_actor->GetName());
// 	}
// }