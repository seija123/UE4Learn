// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{

}


// Called when the game startss
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool USAttributeComponent::ApplyHealthModify(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(NULL, this, Health, Delta);

	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


