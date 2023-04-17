// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/TestAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Abilities/GameplayAbility.h"

UTestAttributeSet::UTestAttributeSet() :
	Life(100.f),
	MaxLife(100.f),
	Mana(100.f),
	ManaMax(100.f)
{}

void UTestAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("Change Speed %d Type %d"), Data.EvaluatedData.Magnitude, Data.EvaluatedData.ModifierOp);
	}
}

void UTestAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetLifeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxLife.GetBaseValue());
	}	

}
