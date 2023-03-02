// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "Engine/World.h"
#include "ActionComponent.h"


void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("StartAction %s"), *GetNameSafe(this));

	if (Instigator)
	{
		UActionComponent* ActionComponent = Cast<UActionComponent>(Instigator->GetComponentByClass(UActionComponent::StaticClass()));
		ActionComponent->ActiveGameplayTags.AppendTags(GrantTags);
	}

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