// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASPlayerController::TogglePause()
{
	if (PauseWidgetInstance != nullptr && PauseWidgetInstance->IsInViewport())
	{
		PauseWidgetInstance->RemoveFromViewport();

		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());

	}

	PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);

	if (PauseWidgetInstance)
	{
		PauseWidgetInstance->AddToViewport(100);

		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
	}

}
