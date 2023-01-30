// Copyright DarkyGr 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	public:
	void OpendDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	private:	
	float CurrentYaw;
	float InitialYaw;
	FRotator OpenDoor;	

	// Set property for edit on UE the Target Yaw
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;

	// Set property for edit on UE the Trigger Volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	// Set property for edit on UE the Trigger Volume
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;
		
};
