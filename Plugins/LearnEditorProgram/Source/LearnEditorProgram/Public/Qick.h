// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "Qick.generated.h"

/**
 * 
 */
UCLASS()
class LEARNEDITORPROGRAM_API UQick : public UAssetActionUtility
{
	GENERATED_BODY()

public:
	UFUNCTION(CallInEditor)
	void TestQAA();
};
