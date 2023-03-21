// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTags.h"
#include "SAction.generated.h"

class UWorld;

USTRUCT()
struct FTestUnrealRpc
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int a = 1;
	UPROPERTY()
	int b = 2;
};

/**
 * 
 */
UCLASS(Blueprintable)
class UE4LEARN_API USAction : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing = "OnRep_IsRunning") //同步的数据来的时候会对比一下是否相异，如果不同的话则会调用回调函数，否则则不会。
	bool IsRunning;

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer GrantTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing = "OnRep_TestUnrealRpcStruct")
	FTestUnrealRpc TestUnrealRpc;


	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	void StartAction_Implementation(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void EndAction(AActor* Instigator);

	void EndAction_Implementation(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION()
	void OnRep_IsRunning();

	UFUNCTION()
	void OnRep_TestUnrealRpcStruct();

	UFUNCTION(BlueprintCallable)
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable)
	bool GetIsRunning() const;

	bool IsSupportedForNetworking() const override
	{
		return true;
	};

	void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
};
