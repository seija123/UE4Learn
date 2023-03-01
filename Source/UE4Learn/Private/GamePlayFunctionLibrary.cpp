// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayFunctionLibrary.h"
#include "SAttributeComponent.h"

bool UGamePlayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	if (TargetActor)
	{
		USAttributeComponent* Attribute = Cast<USAttributeComponent>(TargetActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		Attribute->ApplyHealthModify(DamageCauser, DamageAmount);

		return true;
	}
	return false;
}

bool UGamePlayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, FHitResult& HitResult)
{
	if (UGamePlayFunctionLibrary::ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		HitResult.Component->AddImpulseAtLocation(HitResult.Normal * -10000, HitResult.Location, HitResult.BoneName);
		
		return true;
	}

	return false;
}
