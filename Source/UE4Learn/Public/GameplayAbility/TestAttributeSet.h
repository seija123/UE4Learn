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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Speed);

	//FGameplayAttributeData 的CurrentValue做限制， 在Infinite 或 HasDuration 中会修改CurrentValue。 所以这时可以用这个对属性进行限定。
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//对BaseValue进行限制， GE会在Instant 时修改 BaseValue。所以这时可以用这个对属性进行限定。 
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

};
