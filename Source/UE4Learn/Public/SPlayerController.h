// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class UE4LEARN_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UUserWidget* PauseWidgetInstance;

	UFUNCTION(BlueprintCallable)
	void TogglePause();
	
};
