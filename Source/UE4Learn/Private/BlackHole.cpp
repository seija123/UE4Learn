// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	RootComponent = BoxComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialComp");
	RadialForceComp->ForceStrength = -1000.0f;
	RadialForceComp->bImpulseVelChange = false;
	RadialForceComp->Radius = 100.0F;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(BoxComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");

	
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	//UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnBoxComponentBeginOverlap);
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlackHole::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("ABlackHole::OnBoxComponentBeginOverlap"));
	if (!Cast<APawn>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Not Pawn"));
		OtherActor->Destroy();
	}
}
