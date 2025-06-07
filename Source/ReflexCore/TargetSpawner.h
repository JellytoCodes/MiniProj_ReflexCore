// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

UCLASS()
class REFLEXCORE_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetSpawner();

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	TArray<FVector> targetSpawnLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATargetDummy> targetActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "true"))
	float spawnedDelay = 1.5f;

	int32 maxXPos = 6;
	int32 maxZPos = 6;
	int32 maxSpawn = 7;
	FTimerHandle spawnTimer;

	void SpawnedTarget();
	void GetSpawnedLocation();

	UFUNCTION()
	void SpawnedStart();

	UFUNCTION()
	void SpawnedStop();
};
