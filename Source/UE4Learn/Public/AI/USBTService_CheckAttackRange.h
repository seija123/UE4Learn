// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "USBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class UE4LEARN_API UUSBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	//可用于行为树服务节点直接通过黑板的属性进行配置。
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

};
