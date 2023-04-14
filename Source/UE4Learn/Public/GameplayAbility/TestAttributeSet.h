// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TestAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)

/**
 * 
 */
UCLASS()
class UE4LEARN_API UTestAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UTestAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Life;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Life);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxLife;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, MaxLife);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData ManaMax;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, ManaMax);


};
