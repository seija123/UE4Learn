// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "SCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class ABlackHole;

UCLASS()
class UE4LEARN_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	//TSubclassOf Ӧ������Ҫʹ�õ���̬���Ե�ʱ�򣬱�ȻҪ�õ������͡��Ժ���Ҫ��ĳĳ�����ʱ��ͱ�Ȼ�����������Ϊɶ��Ҳ��֪�������Լ�ס��
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlackHoleClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere)
	UAnimMontage* PrimaryAttackAnim;

	FTimerHandle PrimaryAttackDelayHandle;

	FTimerHandle BlackHoleAttackTimer;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void PrimaryAttack();

	void PrimaryAttackDelay();

	void BlackHoleAttack();
	void BlackHoleAttackDelay();
	
	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

};
