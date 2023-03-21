// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UE4LEARN_API USSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int Score;
	
};
