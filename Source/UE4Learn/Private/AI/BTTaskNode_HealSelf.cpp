// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_HealSelf.h"
#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type UBTTaskNode_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 AAIController* AIC = OwnerComp.GetAIOwner();

	 if (AIC)
	 {
		 APawn* AIPawn = AIC->GetPawn();

		 if (AIPawn)
		 {
			 USAttributeComponent* Attribute = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

			 if (Attribute)
			 {
				 Attribute->ApplyHealthModify(AIPawn, HealAmount);
			 }

		 }

	 }

	return EBTNodeResult::Succeeded;
}