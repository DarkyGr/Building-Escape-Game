// Copyright DarkyGr 2023

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Grabber.h"

#define OUT 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();	// Function for find physics
	SetInputComponent();	// Function for set input component	
}

// Function for find physics
void UGrabber::FindPhysicsHandle()
{
	// Checking for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{		
		//Physics is found
	}
	else
	{
		//Physics isn't found
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on: %s!"), *GetOwner()->GetName());
	}
}

// Function for set input component
void UGrabber::SetInputComponent()
{
	// Checking the input of the player (Keyboard or mouse)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found: %s!"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);		// Bind an action
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);		// Bind an action
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component MISSING!"));
	}
}

// Function for Mesg of Grab
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));

	// TODO, to only raycast when key is pressed and see if we reach any actors with physics body collision channel set

	// If we hit something then attach the physics handle
	// TODO attach physics handle
}

// Function for Mesg of Released
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released..."));

	// TODO remove/release the physics handle
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physic handel is attach
	// Move the onject we are holding

	GetFirstPhysicsBodyInReach();	// Function for detected collision when is reach (1 time)
}


// Function for detected collision when is reach (1 time)
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

		// Get the player view point and set on the varibales
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	FHitResult Hit;
	
	//Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// Body Collision
		TraceParams
	);	

	// See what it hits
	AActor* ActorHit= Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
	}	

	return Hit;
}