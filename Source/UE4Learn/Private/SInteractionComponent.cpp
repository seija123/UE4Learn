// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SItemChest.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryIneract()
{
	FCollisionObjectQueryParams CollisionParam;
	CollisionParam.AddObjectTypesToQuery(ECC_WorldDynamic);
	FVector Start;
	FRotator StartRot;
	FVector End;

	APawn* OwerPawn = Cast<APawn>(GetOwner());
	GetOwner()->GetActorEyesViewPoint(Start, StartRot);
	End = Start + StartRot.Vector() * Length;
	
	FHitResult Hit;
	//GetWorld()->SweepMultiByObjectType();
	bool IsHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, CollisionParam);
	
	if (IsHit && Hit.GetActor()->Implements<UIGamePlayInterface>())
	{
		IIGamePlayInterface::Execute_Interact(Hit.GetActor(), OwerPawn);
	}

	FColor LineColor = IsHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);

	DrawDebugSphere(GetWorld(), Hit.Location, 10, 32, LineColor, false, 2.0f, 0, 2.0f);
}

