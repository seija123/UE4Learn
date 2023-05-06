// Fill out your copyright notice in the Description page of Project Settings.


#include "Qick.h"

void UQick::TestQAA() {

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Cyan, TEXT("TestQAA"));
	}

}