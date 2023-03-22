// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGamePlayInterface.h"
#include "IPreservable.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;
UCLASS()
class UE4LEARN_API ASItemChest : public AActor, public IIGamePlayInterface, public IIPreservable
{
	GENERATED_BODY()

public:
	void Interact_Implementation(APawn* InstigatorPawn);

	void OnActorLoaded_Implementation();

public:	
	// Sets default values for this actor's properties
	ASItemChest();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnyWhere)
	float TargetPitch = 110;

	//UPROPERTY(Replicated, BlueprintReadOnly)
	UPROPERTY(ReplicatedUsing = "OnRep_IsOpened", BlueprintReadOnly, SaveGame)
	bool IsOpened;

	UFUNCTION()
	void OnRep_IsOpened();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

};
