// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_RangeAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "SAttributeComponent.h"


UBTTaskNode_RangeAttack::UBTTaskNode_RangeAttack()
{
	MaxBulletSpeard = 10.f;
}

EBTNodeResult::Type UBTTaskNode_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (ensure(AIController))
	{
		ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());

		if (AIPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));

		if (TargetActor == nullptr || !USAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}


		FVector SpawnLocation = AIPawn->GetMesh()->GetSocketLocation("Muzzle_02");

		FVector Direction = SpawnLocation - AIPawn->GetActorLocation();
		FRotator SpawnRotation = Direction.Rotation();

		SpawnRotation.Yaw = FMath::RandRange(0.f , MaxBulletSpeard);
		SpawnRotation.Pitch = FMath::RandRange(-MaxBulletSpeard, MaxBulletSpeard);

		FActorSpawnParameters SpawnParam;
		SpawnParam.Instigator = AIPawn;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass ,SpawnLocation, SpawnRotation, SpawnParam);
		
		if (NewProjectile == nullptr)
		{
			return EBTNodeResult::Failed;
		}


		return NewProjectile?  EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}


	return EBTNodeResult::Failed;
}
