#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	float open_angle = 85.f;

	UPROPERTY(EditAnywhere)
	float mass_open = 30.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *trigger_volume = nullptr;

	virtual void _open_door();

	virtual void _close_door();

	virtual float get_total_mass();
	virtual void debug();
};