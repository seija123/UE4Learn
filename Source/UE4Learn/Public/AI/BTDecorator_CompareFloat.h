// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CompareFloat.generated.h"


UENUM(BlueprintType)
enum class ECompareTypeCustom :uint8 {
	Equal,
	SmallEqual,
	Less,
	LessEqual,
	Greater,
	GreaterEqual,

};
/**
 * 
 */
UCLASS()
class UE4LEARN_API UBTDecorator_CompareFloat : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector CompareBlackKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float CompareValue;

	UPROPERTY(EditAnywhere, Category = "AI")
	ECompareTypeCustom CompareType;

};


