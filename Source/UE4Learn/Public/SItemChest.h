// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGamePlayInterface.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;
UCLASS()
class UE4LEARN_API ASItemChest : public AActor, public IIGamePlayInterface
{
	GENERATED_BODY()

public:

	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Sets default values for this actor's properties
	ASItemChest();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(VisibleAnyWhere)
	float TargetPitch = 110;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
