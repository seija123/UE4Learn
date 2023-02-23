// Fill out your copyright notice in the Description page of Project Settings.


#include "APowerupActor.h"

// Sets default values
AAPowerupActor::AAPowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAPowerupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPowerupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

