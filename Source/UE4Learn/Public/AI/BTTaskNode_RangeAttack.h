// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_RangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class UE4LEARN_API UBTTaskNode_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTaskNode_RangeAttack();

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxBulletSpeard;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
