// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/SMyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "BrainComponent.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.h"


// Sets default values
ASAICharacter::ASAICharacter()
{

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("Attribute");

	TimeToHitParamName = "TimeToHit";

}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnSeePawn);

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChange);

	HealthUI = CreateWidget<USWorldUserWidget>(GetWorld(), WidgetClass);
	if (HealthUI)
	{
		HealthUI->AttachedActor = this;
		HealthUI->AddToViewport();
	}

}



void ASAICharacter::OnSeePawn(APawn* Pawn)
{
	SetBlackBoardValueTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), "Player SPOTTED", nullptr, FColor::White, 4.0f, true);
	
}

void ASAICharacter::OnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetBlackBoardValueTargetActor(InstigatorActor);
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TEXT(""), GetWorld()->TimeSeconds);

		if (NewHealth <= 0.0f)
		{
			//Stop BT
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			//Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			//Set lifespan
			SetLifeSpan(10.0f);
		}
	}
}

void ASAICharacter::SetBlackBoardValueTargetActor(AActor* TargetActor)
{
	ASMyAIController* AIController = Cast<ASMyAIController>(GetController());

	if (AIController)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();

		if (Blackboard)
		{
			Blackboard->SetValueAsObject("TargetActor", TargetActor);
		}
	}
}


