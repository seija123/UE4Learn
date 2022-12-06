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

bool USAttributeComponent::ApplyHealthModify(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(NULL, this, Health, Delta);

	if (Health <= 0)
	{
		APawn* Pawn = Cast<APawn>(GetOwner());
		if (Pawn != nullptr)
		{
			if (Pawn->Controller != nullptr)
			{
				Pawn->Controller->UnPossess();
			}
				
		}
	}

	return true;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


