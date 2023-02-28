// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
/**
 * 
 */
UCLASS()
class UE4LEARN_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnDotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	FTimerHandle EQSSpawnDotTimerHandle;

	UFUNCTION()
	void SpawnDotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	
public:
	ASGameModeBase();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnActorDie(AActor* Killer, AActor* Victim);

	UFUNCTION()
	void RespawnPlayDelay(AController* PlayerController);

};
