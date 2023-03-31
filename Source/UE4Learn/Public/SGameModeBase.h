// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Engine/DataTable.h"
#include "TestPrimaryDataAsset.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class USSaveGame;
class UDataTable;

USTRUCT(BlueprintType)
struct FTableTest : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int A;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId MonsterId;
};

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

	UPROPERTY(EditDefaultsOnly)
	UDataTable* TableCPPTest;

	UPROPERTY()
	USSaveGame* SaveGameObj;

	UPROPERTY()
	FString SlotName;

	FTimerHandle EQSSpawnDotTimerHandle;

	UFUNCTION()
	void SpawnDotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnLoadMonsterComplete(FPrimaryAssetId MonsterId, FVector Location);
	
public:
	ASGameModeBase();

	virtual void StartPlay() override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnActorDie(AActor* Killer, AActor* Victim);

	UFUNCTION()
	void RespawnPlayDelay(AController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

};
