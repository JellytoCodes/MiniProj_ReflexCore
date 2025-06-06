// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "TargetDummy.h"

// Sets default values
ATargetSpawner::ATargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	for(int xPos = 0 ; xPos < maxXPos ; xPos++)
	{
		for(int zPos = 0 ; zPos < maxZPos ; zPos++)
		{
			targetSpawnLocation.Add(FVector(GetActorLocation().X + (xPos * 100), GetActorLocation().Y, GetActorLocation().Z + (zPos * 100)));
		}
	}

	FTimerHandle spawnTimer;
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ATargetSpawner::SpawnedTarget, spawnedDelay, true);
}

void ATargetSpawner::SpawnedTarget()
{
	int32 randSpawn = FMath::RandRange(0, targetSpawnLocation.Num() - 1);
	const FVector spawnPos = targetSpawnLocation[randSpawn];

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
	GetWorld()->SpawnActor<ATargetDummy>(targetActor, spawnPos, FRotator::ZeroRotator, spawnParams);
}