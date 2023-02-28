// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CompareFloat.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_CompareFloat::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	float BlackboardVal = BlackBoard->GetValueAsFloat(CompareBlackKey.SelectedKeyName);

	switch (CompareType)
	{
	case ECompareTypeCustom::Equal:
		return BlackboardVal == CompareValue;
	case ECompareTypeCustom::SmallEqual:
		return BlackboardVal <= CompareValue;
	case ECompareTypeCustom::Less:
		return BlackboardVal < CompareValue;
	case ECompareTypeCustom::LessEqual:
		return BlackboardVal <= CompareValue;
	case ECompareTypeCustom::Greater:
		return BlackboardVal > CompareValue;
	case ECompareTypeCustom::GreaterEqual:
		return BlackboardVal >= CompareValue;
	default:
		return false;
	}

	
}