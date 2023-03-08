// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "ActionComponent.generated.h"

class USAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4LEARN_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<USAction*> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<USAction>> ActionTemplates;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddAction(TSubclassOf<USAction> Action);

	UFUNCTION(BlueprintCallable)
	virtual void StartAction(FName ActionName);

	UFUNCTION(BlueprintCallable)
	virtual void StopAction(FName ActionName);

	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer ActiveGameplayTags;

	
};
