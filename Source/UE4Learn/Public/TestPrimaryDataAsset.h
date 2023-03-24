// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TestPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UE4LEARN_API UTestPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> Monster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;
	
};
