// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickAssetAction.h"

void UQuickAssetAction::TestQAA() {

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Cyan, TEXT("TestQAA"));
	}

}