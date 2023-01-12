// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class UE4LEARN_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

	UPROPERTY(EditAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	virtual void PostInitializeComponents() override;

	//����ue4ί�б���Ҫ��UFUNCTION
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

};
