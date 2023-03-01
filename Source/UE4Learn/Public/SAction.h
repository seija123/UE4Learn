// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE4LEARN_API USAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	//UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	void StartAction_Implementation(AActor* Instigator);

	//UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void EndAction(AActor* Instigator);

	void EndAction_Implementation(AActor* Instigator);
};
