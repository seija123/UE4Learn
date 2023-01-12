// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/SMyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ASAICharacter::ASAICharacter()
{

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnSeePawn);
}

void ASAICharacter::OnSeePawn(APawn* Pawn)
{
	ASMyAIController* AIController = Cast<ASMyAIController>( Pawn->GetController());

	if (AIController)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		
		if (Blackboard)
		{
			Blackboard->SetValueAsObject("TargetActor", Pawn);
		}
		
		DrawDebugString(GetWorld(), GetActorLocation(), "Player SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}


