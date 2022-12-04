// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_CPPTest.generated.h"

/**
 * 
 */
UCLASS()
class UE4LEARN_API UBTTaskNode_CPPTest : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	int Count = 0;
	
	
public:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
