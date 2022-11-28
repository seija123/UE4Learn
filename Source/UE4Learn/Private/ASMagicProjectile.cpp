// Fill out your copyright notice in the Description page of Project Settings.


#include "ASMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"


// Sets default values
AASMagicProjectile::AASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AASMagicProjectile::OnBegineOverlap);
}

// Called when the game starts or when spawned
void AASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASMagicProjectile::OnBegineOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKill())
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("haha"));
	if (OtherActor && OtherActor != GetInstigator())
	{
		UE_LOG(LogTemp, Log, TEXT("!!!!"));
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp != nullptr)
		{
			AttributeComp->ApplyHealthModify(-20.0f);
		}
		
		Destroy();
	}
}

// Called every frame
void AASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

