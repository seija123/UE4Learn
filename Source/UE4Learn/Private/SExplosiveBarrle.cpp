// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrle.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASExplosiveBarrle::ASExplosiveBarrle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	ForceComponent = CreateDefaultSubobject<URadialForceComponent>("ForceComponent");
	ForceComponent->SetupAttachment(RootComponent);
	ForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
	
	ForceComponent->SetAutoActivate(false);
	ForceComponent->Radius = 750.0f;
	ForceComponent->ImpulseStrength = 1000.0f;
	ForceComponent->bImpulseVelChange = false;

	//老师不在构造函数中绑定这些构造是因为当使用ue4热重载的时候有可能不生效，只能通过IDE进行重新编译。他的版本有些老了所以暂时先记录一下。另外绑定受击事件的还有PostInitializeComponents（初始化组件之后），或者是BeginPlay。
	//BaseMesh->OnComponentHit.__Internal_AddDynamic(this, &ASExplosiveBarrle::OnHit);
}

void ASExplosiveBarrle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BaseMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrle::OnHit);
}

// Called when the game starts or when spawned
void ASExplosiveBarrle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASExplosiveBarrle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrle::OnHit(UPrimitiveComponent* HitComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit)
{
	ForceComponent->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("Log_Temp Log"));


	UE_LOG(LogTemp, Warning, TEXT("Log_Temp Warning"));

	UE_LOG(LogTemp, Warning, TEXT("Log_Temp Warning %s, at game time %f"), *GetNameSafe(Other), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT(" Hit Point Is %s"),Hit.Location.ToString());
	DrawDebugString(GetWorld(), Hit.Location, *CombinedString);
	//https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html
	//忘记了跑来康康，几种log方式。
}