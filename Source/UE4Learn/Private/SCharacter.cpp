// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "Animation/AnimMontage.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	//���ɱ�ʹ�ÿ���������ת�����Ϊfalse�Ļ�ֻ��ʹ�����λ�á�
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);	

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");

	//ʹ���ƶ��������ת��
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	//��ʹ�ÿ���������תYaw����ֵ�ᡣ
	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	//��������ˮƽ����ֱ��
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);

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
	//ֻ��Ҫ��������ˮƽ������ת�ᡣ
	FRotator Rotate = GetControlRotation();
	Rotate.Pitch = 0.0f;
	Rotate.Roll = 0.0f;
	
	//������ת��ȡ������Ӧ��ķ�����������ʽ��Rotate.Vector()����ֱ�ӻ�ȡ��ǰ��������Ҳ����X���������
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
	FVector Location = GetMesh()->GetSocketLocation("Muzzle_02");

	FTransform ActorTM = FTransform(GetActorRotation(), Location);
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, ActorTM, SpawnParam);
}

void ASCharacter::PrimaryInteract()
{
	
	InteractionComponent->PrimaryIneract();
}


