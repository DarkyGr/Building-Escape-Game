// Copyright DarkyGr 2023


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	// Set values variables
	InitialYaw = GetOwner()->GetActorRotation().Yaw;	// Actor Yaw
	CurrentYaw = InitialYaw;	// Set Current Yaw == Actor Yaw
	TargetYaw += InitialYaw;	// Set 90 grades of Target
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());	// Msg 1
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);	// Msg 2
	
	// Set actor rotation for animated anywhere
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 1.25f);		// Set animated of actor
	// Delta Time may affect game performance and item reaction time -> For this reason used DeltaTime * 0.5f
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();		// Create and set FRotator with Actor
	DoorRotation.Yaw = CurrentYaw;		// Set FRotation Yaw of Current Yaw
	GetOwner()->SetActorRotation(DoorRotation);		// Set Rotation
}

