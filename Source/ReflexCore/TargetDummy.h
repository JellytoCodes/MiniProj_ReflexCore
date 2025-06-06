// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetDummy.generated.h"

UCLASS()
class REFLEXCORE_API ATargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetDummy();

	void TargetDestroy();

protected:
	virtual void BeginPlay() override;

private :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* targetMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
	float lifeSpan = 1.5f;

	FTimerHandle lifeTimer;
};
