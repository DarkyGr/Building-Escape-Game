// Copyright DarkyGr 2023

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Grabber.h"

#define OUT 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

		// Get the player view point and set on the varibales
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

		// Msg for view in terminal the result
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s - Rotation: %s"), 
	// 	*PlayerViewPointLocation.ToString(), 
	// 	*PlayerViewPointRotation.ToString()
	// );

	// Draw a line fromm player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),		//World
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),		//Color line
		false,
		0.f,
		0,
		5.f		//pixels
	);

	// Logging out to test

	//Ray-cast out to a certain distance (Reach)

	// See what it hits


}

