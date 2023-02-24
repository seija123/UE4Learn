// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4LEARN_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attribute", meta = (DisplayName = "GetAttribute"))
	static USAttributeComponent* GetAttributeFromActor(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attribute", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* FromActor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	 
	UPROPERTY(EditDefaultsOnly ,BlueprintReadOnly)
	float Health = 100.0f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	bool ApplyHealthModify(AActor* Instigator, float Delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
		
};
