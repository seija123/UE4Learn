// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/USBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UUSBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));

		if (TargetActor == nullptr)
		{
			return;
		}

		AAIController* AIController = OwnerComp.GetAIOwner();

		APawn* AIPawn = AIController->GetPawn();

		if (ensure(AIPawn))
		{
			float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

			bool bWithinRange = Distance < 1000.0f;

			bool bHasLOS = AIController->LineOfSightTo(TargetActor);
			
			BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));
		}

	}

}