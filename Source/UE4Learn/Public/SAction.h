// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTags.h"
#include "SAction.generated.h"

class UWorld;
/**
 * 
 */
UCLASS(Blueprintable)
class UE4LEARN_API USAction : public UObject
{
	GENERATED_BODY()

protected:
	bool IsRunning;

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer GrantTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	void StartAction_Implementation(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void EndAction(AActor* Instigator);

	void EndAction_Implementation(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);


	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable)
	bool GetIsRunning() const;
};
