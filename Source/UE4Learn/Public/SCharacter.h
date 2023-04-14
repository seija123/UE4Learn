// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "SCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class ABlackHole;
class USAttributeComponent;
class UActionComponent;
class USAction;
class UAbilitySystemComponent;
class UGameplayAbility;
class UTestAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGASHealthChanged, float, NewHealth);

UCLASS()
class UE4LEARN_API ASCharacter : public ACharacter, public IGameplayTagAssetInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ASCharacter();

	UPROPERTY(BlueprintReadWrite)
	int PlayerScore;

protected:
	//TSubclassOf Ӧ������Ҫʹ�õ���̬���Ե�ʱ�򣬱�ȻҪ�õ������͡��Ժ���Ҫ��ĳĳ�����ʱ��ͱ�Ȼ�����������Ϊɶ��Ҳ��֪�������Լ�ס��
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlackHoleClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> GodFlashTargetClass;

	AActor* GodFlashTarget;

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

	UPROPERTY(EditAnyWhere)
	FGameplayTagContainer GameplayTagList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UActionComponent* ActionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTestAttributeSet* AttributeSet;


	FTimerHandle PrimaryAttackDelayHandle;

	FTimerHandle BlackHoleAttackTimer;

	FTimerHandle GodFlashTimer;

	UPROPERTY(BlueprintAssignable)
	FOnGASHealthChanged OnGASHealthChanged;

	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(Server, Reliable)
	void ServerPrimaryAttack();

	void PrimaryAttack();

	UFUNCTION(NetMulticast, UnReliable)
	void ClientPrimaryAttack();

	void PrimaryAttackDelay();

	void BlackHoleAttack();
	void BlackHoleAttackDelay();
	
	void PrimaryInteract();

	void GodFlash();
	void DelayGodFlash();
	void DelayGodFlashTeleport();

	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	FTransform GetPrimaryAttackTramsform();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	// ͨ�� IGameplayTagAssetInterface �̳�
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;

	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100.f);

	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void EndSprint();

	UFUNCTION(BlueprintCallable)
	void GainScore();

	// ͨ�� IAbilitySystemInterface �̳�
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void GiveAbility(TSubclassOf<UGameplayAbility> Ability);
};
