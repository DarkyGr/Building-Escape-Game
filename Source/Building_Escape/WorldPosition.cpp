// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();		//Set variable for name actor
	FVector ObjectPosition = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("The name actor is: %s"), *ObjectName);	// Name of actor 
	UE_LOG(LogTemp, Error, TEXT("The location actor is: \nX-> %f \nY-> %f \nZ-> %f"), ObjectPosition.X, ObjectPosition.Y, ObjectPosition.Z);	// Name of actor 

	// ----------- Others options ------------------------------

	// FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("The name actor is: %s. \nAnd position is: %s"), *ObjectName, *ObjectPosition);	// Name of actor 

	// FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToString();
	// UE_LOG(LogTemp, Warning, TEXT("The name actor is: %s. \nAnd position is: %s"), *ObjectName, *ObjectPosition);	// Name of actor 
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

