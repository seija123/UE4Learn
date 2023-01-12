// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SMyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASMyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	UBlackboardComponent* MyBlackBoard = GetBlackboardComponent();
	if (MyBlackBoard != nullptr)
	{
		//APawn* Player1 = UGameplayStatics::GetPlayerPawn(this, 0);
		//MyBlackBoard->SetValueAsVector("Target", Player1->GetActorLocation());

		//MyBlackBoard->SetValueAsObject("TargetActor", Player1);

		//MyBlackBoard->SetValueAsString("TestCompareBBEntriesDecorator1", "haha");
		//MyBlackBoard->SetValueAsString("TestCompareBBEntriesDecorator2", "haha");

		
	}
	
}

