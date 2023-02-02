// Copyright DarkyGr 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

//Add new Struct
struct FPlayerViewPoint
{
    FVector Location;    
	FRotator Rotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;	// Null pointer = nullptr
	UInputComponent* InputComponent = nullptr;
	
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetInputComponent();	

	//Return the fisrt Actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetGrabLocation() const;
	FPlayerViewPoint GetPlayerViewPoint() const;
};
