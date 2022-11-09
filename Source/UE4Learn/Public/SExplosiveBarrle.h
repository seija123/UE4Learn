// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrle.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class UE4LEARN_API ASExplosiveBarrle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* BaseMesh;

	UPROPERTY()
	URadialForceComponent* ForceComponent;

	virtual void PostInitializeComponents() override;

	void OnHit(UPrimitiveComponent* HitComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
