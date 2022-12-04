// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_CPPTest.h"

void UBTTaskNode_CPPTest::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Count = Count + 1;

	FString aa = FString::FromInt(Count);

	UE_LOG(LogTemp, Warning, TEXT("aa %d !!!"), Count);

}

EBTNodeResult::Type UBTTaskNode_CPPTest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	Count = Count + 1;

	FString aa = FString::FromInt(Count);

	UE_LOG(LogTemp, Warning, TEXT("aa %d !!!"), Count);

	return EBTNodeResult::Type::Succeeded;
}

void UBTTaskNode_CPPTest::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	//bCreateNodeInstance = true;
}
