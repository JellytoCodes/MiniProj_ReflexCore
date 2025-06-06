// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

ATargetDummy::ATargetDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	targetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	RootComponent = targetMesh;
}

void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(lifeTimer, this, &ATargetDummy::TargetDestroy, lifeSpan, false);
}

void ATargetDummy::TargetDestroy()
{
	GetWorldTimerManager().ClearTimer(lifeTimer);
	Destroy();
}



