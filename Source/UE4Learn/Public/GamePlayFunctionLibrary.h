// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GamePlayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE4LEARN_API UGamePlayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, FHitResult& HitResult);



};
