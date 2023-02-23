// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Patrol.h"
#include "AIController.h"

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	OwnerComp.GetAIOwner()->GetPawn()->GetMovementComponent();
}