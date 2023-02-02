// Copyright DarkyGr 2023

#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

// Function for set input component
void UGrabber::SetInputComponent()
{
	// Checking the input of the player (Keyboard or mouse)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Input component found: %s!"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);		// Bind an action
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);		// Bind an action
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component MISSING!"));
	}
}

// Function for find physics
void UGrabber::FindPhysicsHandle()
{
	// Checking for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{		
		//Physics isn't found
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on: %s!"), *GetOwner()->GetName());
	}
}

// Function for Mesg of Grab
void UGrabber::Grab()
{
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));	

	FHitResult HitResult = GetFirstPhysicsBodyInReach();	// Function for detected collision when is reach (1 time)
	AActor* ActorHitResult = HitResult.GetActor();			// Save the Hit Result on Actor pointer
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();	//Create varibale for the component of Hit Result	

	// If we hit something then attach the physics handle
	if (ActorHitResult)	//Check Actor (Pointer)
	{
		if (!PhysicsHandle){return;}
		// TODO attach physics handle
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			GetGrabLocation()
		);
	}	
}

// Function for Mesg of Released
void UGrabber::Release()
{
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Released..."));

	if (!PhysicsHandle){return;}
	// TODO remove/release the physics handle
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physic handel is attach
	if (!PhysicsHandle){return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move the onject we are holding
		PhysicsHandle->SetTargetLocation(GetGrabLocation());
	}		
}

// Function for detected collision when is reach (1 time)
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;	
	//Ray-cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerViewPoint().Location,
		GetGrabLocation(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// Body Collision
		TraceParams
	);	

	// See what it hits
	AActor* ActorHit= Hit.GetActor();

	if (ActorHit)	//Msg if the player grabbed object
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *(ActorHit->GetName()));
	}	

	return Hit;
}

// Function for set parameters in the new struct
FPlayerViewPoint UGrabber::GetPlayerViewPoint() const
{
	FPlayerViewPoint PlayerPointView;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerPointView.Location, 
		OUT PlayerPointView.Rotation
	);

	return PlayerPointView;
}

// Function for calcule the position and transform, to return FVector
FVector UGrabber::GetGrabLocation() const
{
	FPlayerViewPoint NewPlayerPointView = GetPlayerViewPoint();

	// Draw a line from player showing the reach
	FVector LineTraceEnd = NewPlayerPointView.Location + NewPlayerPointView.Rotation.Vector() * Reach;

	return LineTraceEnd;
}