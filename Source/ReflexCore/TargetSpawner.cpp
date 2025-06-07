// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "TargetDummy.h"
#include "ReflexCoreGameMode.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

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
	
	GetSpawnedLocation();

	auto* gameMode = Cast<AReflexCoreGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(gameMode)
	{
		auto manager = gameMode->GetGameManager();
		if(manager)
		{
			manager->startOnBroadCast.AddDynamic(this, &ATargetSpawner::SpawnedStart);
			manager->endOnBroadCast.AddDynamic(this, &ATargetSpawner::SpawnedStop);
		}
	}
}

void ATargetSpawner::SpawnedTarget()
{
	TArray<int32> shuffledIndices;
	for (int32 i = 0; i < targetSpawnLocation.Num(); i++)
	{
		shuffledIndices.Add(i);
	}
	shuffledIndices.Sort([](int32 A, int32 B) {
		return FMath::RandBool(); // ¼ÅÇÃ È¿°ú
	});

	for (int32 curSpawn = 0; curSpawn < maxSpawn && curSpawn < shuffledIndices.Num(); curSpawn++)
	{
		int32 index = shuffledIndices[curSpawn];
		const FVector spawnPos = targetSpawnLocation[index];

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<ATargetDummy>(targetActor, spawnPos, FRotator::ZeroRotator, spawnParams);
	}
}

void ATargetSpawner::GetSpawnedLocation()
{
	for(int xPos = 0 ; xPos < maxXPos ; xPos++)
	{
		for(int zPos = 0 ; zPos < maxZPos ; zPos++)
		{
			targetSpawnLocation.Add(FVector(GetActorLocation().X + (xPos * 75), GetActorLocation().Y, GetActorLocation().Z + (zPos * 75)));
		}
	}
}

void ATargetSpawner::SpawnedStart()
{
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ATargetSpawner::SpawnedTarget, spawnedDelay, true);
}

void ATargetSpawner::SpawnedStop()
{
	GetWorldTimerManager().ClearTimer(spawnTimer);
}
