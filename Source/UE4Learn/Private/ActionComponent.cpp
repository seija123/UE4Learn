// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "SAction.h"
#include "Engine/Engine.h"
#include "../UE4Learn.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FGameplayTag tagtag = FGameplayTag::RequestGameplayTag(TEXT("Player"), true);

	SetIsReplicatedByDefault(true);
}


void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		for (TSubclassOf<USAction> ActionClass : ActionTemplates)
		{
			AddAction(ActionClass);
		}
	}
	
	
}


void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FString DebugMessage = GetNameSafe(GetOwner()) + ":" + ActiveGameplayTags.ToStringSimple();

	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::White, DebugMessage );

	for (USAction* Action : Actions)
	{
		FString Msg = FString::Printf(TEXT("ActorName %s, ActionName %s, IsRunning %s"), *GetNameSafe(GetOwner()), *Action->ActionName.ToString(), Action->GetIsRunning()? TEXT("True"): TEXT("False"));

		LogOnScreen(GetOwner(), Msg, FColor::White, 0.f);
	}
	
}

void UActionComponent::AddAction(TSubclassOf<USAction> ActionClass)
{
	if (!ActionClass)
	{
		return;
	}
	 
	USAction* NewAction = NewObject<USAction>(GetOwner(), ActionClass);

	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

void UActionComponent::StartAction_Implementation(FName ActionName)
{
	for (auto Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StartAction(GetOwner());
		}
	}

}

void UActionComponent::StopAction_Implementation(FName ActionName)
{
	for (auto Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->EndAction(GetOwner());
		}
	}
}

bool UActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (auto Action: Actions)
	{
		if (Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

void UActionComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UActionComponent, Actions);
}


