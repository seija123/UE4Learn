// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class UPawnSensingComponent;
class USAttributeComponent;
class UUserWidget;
class USWorldUserWidget;

UCLASS()
class UE4LEARN_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

	UPROPERTY(EditAnywhere, Category = "AI")
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	USAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UPROPERTY()
	USWorldUserWidget* HealthUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;
	

	virtual void PostInitializeComponents() override;

	//监听ue4委托必须要加UFUNCTION
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	void OnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	void SetBlackBoardValueTargetActor(AActor* TargetActor);
};
