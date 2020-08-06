#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyTriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//UCLASS()
class ATP_PROJECT_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void _open_door();
	
	virtual void _close_door();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY(VisibleAnywhere)
		float open_angle = 85.f;

	UPROPERTY(EditAnywhere)
		AMyTriggerVolume* trigger_volume;



	UPROPERTY(EditAnywhere)
		float close_delay = 1.f ;

		float close_time;

	// UPROPERTY(EditAnywhere)
		AActor* actor_accept;
		AActor* this_owner;
};