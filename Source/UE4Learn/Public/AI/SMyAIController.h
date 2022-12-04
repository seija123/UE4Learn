// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SMyAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class UE4LEARN_API ASMyAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
};
