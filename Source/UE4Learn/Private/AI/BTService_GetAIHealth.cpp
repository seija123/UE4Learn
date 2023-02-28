// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_GetAIHealth.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_GetAIHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	if (AIC)
	{
		APawn* AIPawn = AIC->GetPawn();
		if (ensureMsgf(AIPawn, TEXT("AIController's Pawn isNull")))
		{
			USAttributeComponent* AIAttribute = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
			UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

			if (IsValid(AIAttribute) && IsValid(Blackboard))
			{
				Blackboard->SetValueAsFloat(BlackBoardKey.SelectedKeyName, AIAttribute->GetHealth());
			}
			
		}
		
	
	}

}