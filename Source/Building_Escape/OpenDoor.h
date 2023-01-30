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
	float DoorLastOpened = 0.f;	

	// Set property for edit on UE the Target Yaw
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	// Set property for edit on UE the Door Open Speed
	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 3.f;

	// Set property for edit on UE the Door Close Speed
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 0.8f;

	// Set property for edit on UE the Door Close Selay
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	// Set property for edit on UE the Trigger Volume
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	// Set property for edit on UE the Trigger Volume
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;
		
};
