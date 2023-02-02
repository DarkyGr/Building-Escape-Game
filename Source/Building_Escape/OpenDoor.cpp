// Copyright DarkyGr 2023

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Set values variables
	InitialYaw = GetOwner()->GetActorRotation().Yaw;	// Actor Yaw
	CurrentYaw = InitialYaw;	// Set Current Yaw == Actor Yaw
	OpenAngle += InitialYaw;	// Set 90 grades of Target

	// Check if the pressure plate is not set
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has open door component on it, but no pressure plate set!"), *GetOwner()->GetName())
	}

	// Search in the world for the first pawn Player
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if the actor is stepping on the pressure plate	
	if(TotalMassOfActors() >= MassToOpenDoors){
		OpendDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		// The time difference between the world and dooropene is greater than doorclose and wait 2 seconds for close the door
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}		
	}
}

// Function for Open Door
void UOpenDoor::OpendDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());	// Msg 1
	// UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);	// Msg 2
	
	// Set actor rotation for animated anywhere
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);		// Set animated of actor
	// Delta Time may affect game performance and item reaction time -> For this reason used DeltaTime * 0.5f
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();		// Create and set FRotator with Actor
	DoorRotation.Yaw = CurrentYaw;		// Set FRotation Yaw of Current Yaw
	GetOwner()->SetActorRotation(DoorRotation);		// Set Rotation
}

// Function for Close Door
void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);		// Set animated of actor	
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();		// Create and set FRotator with Actor
	DoorRotation.Yaw = CurrentYaw;		// Set FRotation Yaw of Current Yaw
	GetOwner()->SetActorRotation(DoorRotation);		// Set Rotation
}

// Fucntion for return the total mass of the objects
float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// UE_LOG(LogTemp, Warning, TEXT("%i Actors!"), OverlappingActors.Num());

	// Add up their masses
	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		// UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate!"), *Actor->GetName());
	}
	

	return TotalMass;
}