// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "Engine/World.h"
#include "ActionComponent.h"
#include "Net/UnrealNetwork.h"
#include "../UE4Learn.h"


void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StartAction %s"), *GetNameSafe(this));

	if (!CanStart(Instigator))
	{
		return;
	}

	if (Instigator)
	{
		UActionComponent* ActionComponent = Cast<UActionComponent>(Instigator->GetComponentByClass(UActionComponent::StaticClass()));
		ActionComponent->ActiveGameplayTags.AppendTags(GrantTags);
	}

	TestUnrealRpc.a += 1;
	TestUnrealRpc.b += 1;

	IsRunning = true;
}



void USAction::EndAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StartAction %s"), *GetNameSafe(this));

	if (Instigator)
	{
		UActionComponent* ActionComponent = Cast<UActionComponent>(Instigator->GetComponentByClass(UActionComponent::StaticClass()));
		ActionComponent->ActiveGameplayTags.RemoveTags(GrantTags);
	}

	IsRunning = false;
}

void USAction::OnRep_IsRunning()
{
	FString Msg = FString::Printf(TEXT("IsRunning is %s"), IsRunning? TEXT("True"):TEXT("False"));
	LogOnScreen(this, Msg);
}

void USAction::OnRep_TestUnrealRpcStruct()
{
	//UE_LOG(LogTemp, Log, TEXT("OnRep_TestUnrealRpcStruct a %d b %d"), TestUnrealRpc.a, TestUnrealRpc.b);
	FString Msg = FString::Printf(TEXT("OnRep_TestUnrealRpcStruct a %d b %d"), TestUnrealRpc.a, TestUnrealRpc.b);
	LogOnScreen(this, Msg);

}

UWorld* USAction::GetWorld() const
{
	AActor* Actor = Cast<AActor>(GetOuter());

	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

bool USAction::GetIsRunning() const
{
	return IsRunning;
}

void USAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAction, IsRunning);
	DOREPLIFETIME(USAction, TestUnrealRpc);
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning)
	{
		return false;
	}

	if (Instigator)
	{
		UActionComponent* ActionComponent = Cast<UActionComponent>(Instigator->GetComponentByClass(UActionComponent::StaticClass()));
		return  !ActionComponent->ActiveGameplayTags.HasAny(BlockedTags);
	}

	return true;

}