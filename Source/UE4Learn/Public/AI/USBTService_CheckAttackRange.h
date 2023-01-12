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
	
	//��������Ϊ������ڵ�ֱ��ͨ���ڰ�����Խ������á�
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

};
