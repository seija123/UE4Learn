// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AI/SAICharacter.h"
#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "Curves/CurveFloat.h"
#include "SCharacter.h"

static TAutoConsoleVariable<bool> IsCanSpawnBot(TEXT("su.CanSpawnBot"), true, TEXT("CanSpawnBot !!!"), ECVF_Cheat);

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(EQSSpawnDotTimerHandle, this, &ASGameModeBase::SpawnDotTimerElapsed ,SpawnTimerInterval, true);

}



void ASGameModeBase::SpawnDotTimerElapsed()
{

	if (!IsCanSpawnBot.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Log, TEXT("IsCanSpawnBot is false"));
		return;
	}

	int NumOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp && AttributeComp->IsAlive())
		{
			NumOfAliveBots++;
		}
	}

	int MaxCount = 10;

	if (DifficultyCurve)
	{
		MaxCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfAliveBots >= MaxCount)
	{
		return;
	}


	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnDotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr );

	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Dot EQS Query Failed !"));
		return; 
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}


void ASGameModeBase::OnActorDie(AActor* Killer, AActor* Victim)
{
	ASCharacter* Player = Cast<ASCharacter>(Victim);
	if (Player)
	{
		FTimerHandle RespawnPlayerTimer;

		FTimerDelegate RespawnDelegate;

		RespawnDelegate.BindUFunction(this, "RespawnPlayDelay", Player->GetController());

		GetWorld()->GetTimerManager().SetTimer(RespawnPlayerTimer, RespawnDelegate, 2.f, false);
	}

}

void ASGameModeBase::RespawnPlayDelay(AController* PlayerController)
{
	if (PlayerController)
	{
		PlayerController->UnPossess();

		RestartPlayer(PlayerController);
	}
}
