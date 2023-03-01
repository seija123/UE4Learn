// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "SAction.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UActionComponent::AddAction(TSubclassOf<USAction> ActionClass)
{
	if (!ActionClass)
	{
		return;
	}

	USAction* NewAction = NewObject<USAction>(ActionClass);

	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

void UActionComponent::StartAction(FName ActionName)
{
	for (auto Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StartAction(GetOwner());
		}
	}

}

void UActionComponent::StopAction(FName ActionName)
{
	for (auto Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->EndAction(GetOwner());
		}
	}
}


