// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//弹簧臂使用控制器的旋转。如果为false的话只会使用相对位置。
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);	

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");

	//Attribute = CreateDefaultSubobject<USAttributeComponent>("Attribute");

	//使用移动组件的旋转。
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	//不使用控制器的旋转Yaw，数值轴。
	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Attribute->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth)
	{
		UE_LOG(LogTemp, Log, TEXT("OnHealthChanged !!!"));
	}

}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	//控制器的水平和竖直。
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("BlackHoleAttack", IE_Pressed, this, &ASCharacter::BlackHoleAttack);

	PlayerInputComponent->BindAction("GodFlash", IE_Pressed, this, &ASCharacter::GodFlash);

}


//GameplayTag系统，CheckGameplayTasOnActor的行为树节点必须要用的东西。
void ASCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTagList;
}

bool ASCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{

	return GameplayTagList.HasTag(TagToCheck);
}

bool ASCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTagList.HasAll(TagContainer);
}

bool ASCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTagList.HasAny(TagContainer);
}

void ASCharacter::HealSelf(float Amount /* = 100 */)
{
	USAttributeComponent* MyAttribute = Cast<USAttributeComponent>(GetComponentByClass(USAttributeComponent::StaticClass()));

	MyAttribute->ApplyHealthModify(this, Amount);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator Rotate = GetControlRotation();
	Rotate.Pitch = 0.0f;
	Rotate.Roll = 0.0f;

	FVector ForwardVector = FRotationMatrix(Rotate).GetScaledAxis(EAxis::X);
	
	AddMovementInput(ForwardVector, Value);
}

void ASCharacter::MoveRight(float Value)
{
	//只需要控制器的水平方向旋转轴。
	FRotator Rotate = GetControlRotation();
	Rotate.Pitch = 0.0f;
	Rotate.Roll = 0.0f;
	
	//根据旋转获取坐标相应轴的方向向量，方式。Rotate.Vector()可以直接获取向前的向量，也就是X轴的向量。
	FVector RightVector = FRotationMatrix(Rotate).GetScaledAxis(EAxis::Y);


	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	//UE_LOG(LogTemp, Warning, TEXT("AHAHAHA"));
	PlayAnimMontage(PrimaryAttackAnim);

	GetWorldTimerManager().SetTimer(PrimaryAttackDelayHandle, this, &ASCharacter::PrimaryAttackDelay, 0.2f);	
	//GetWorldTimerManager().ClearTimer(PrimaryAttackDelayHandle);
}

void ASCharacter::PrimaryAttackDelay()
{
	
	FTransform ActorTM = GetPrimaryAttackTramsform();
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, ActorTM, SpawnParam);
}


void ASCharacter::BlackHoleAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	GetWorldTimerManager().SetTimer(BlackHoleAttackTimer, this, &ASCharacter::BlackHoleAttackDelay, 0.2f);
}

FTransform ASCharacter::GetPrimaryAttackTramsform()
{
	FVector Location = GetMesh()->GetSocketLocation("Muzzle_02");

	FVector CameraLocation = CameraComp->K2_GetComponentLocation();
	FVector LineEnd = CameraLocation + CameraComp->GetForwardVector() * 1000;

	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionQueryParams;
	CollisionQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	bool IsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, LineEnd, CollisionQueryParams);

	/*if (!ensure(IsHit))
	{
		UE_LOG(LogTemp, Log, TEXT("Not Hit!!!"));
	}*/

	FVector TargetLoc = IsHit ? HitResult.Location : LineEnd;

	FRotator Rot;
	Rot = UKismetMathLibrary::FindLookAtRotation(Location, TargetLoc);

	FTransform ActorTM = FTransform(Rot, Location);

	return ActorTM;

}

void ASCharacter::BlackHoleAttackDelay()
{
	
	auto ActorTM = GetPrimaryAttackTramsform();

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;

	GetWorld()->SpawnActor<AActor>(BlackHoleClass, ActorTM, SpawnParam);

}

void ASCharacter::PrimaryInteract()
{
	
	InteractionComponent->PrimaryIneract();
}


void ASCharacter::GodFlash()
{

	PlayAnimMontage(PrimaryAttackAnim);

	GetWorldTimerManager().SetTimer(GodFlashTimer, this, &ASCharacter::DelayGodFlash, 0.2f);
}

void ASCharacter::DelayGodFlash()
{
	auto ActorTM = GetPrimaryAttackTramsform();

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;

	GodFlashTarget = GetWorld()->SpawnActor<AActor>(GodFlashTargetClass, ActorTM, SpawnParam);
	GetWorldTimerManager().SetTimer(GodFlashTimer, this, &ASCharacter::DelayGodFlashTeleport, 1.0f);
}

void ASCharacter::DelayGodFlashTeleport()
{
	SetActorLocation(GodFlashTarget->GetActorLocation());
	GodFlashTarget->Destroy();
}