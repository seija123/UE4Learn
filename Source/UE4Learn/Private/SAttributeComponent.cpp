// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

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

bool USAttributeComponent::ApplyHealthModify(AActor* Instigator, float Delta)
{
	APawn* Pawn = Cast<APawn>(Instigator);

	if (!Pawn->CanBeDamaged())
	{
		return false;
	}

	Health += Delta;

	OnHealthChanged.Broadcast(Instigator, this, Health, Delta);

	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

USAttributeComponent* USAttributeComponent::GetAttributeFromActor(AActor* FromActor)
{
	return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
}

bool USAttributeComponent::IsActorAlive(AActor* FromActor)
{
	USAttributeComponent* Attributes = Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (Attributes)
	{
		return Attributes->IsAlive();
	}

	return false;
}

