// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HitManager.generated.h"

class ATextDisplayActor;

UCLASS()
class REFLEXCORE_API UHitManager : public UObject
{
	GENERATED_BODY()

public :
	void Init(ATextDisplayActor* inScoreActor, ATextDisplayActor* inAccuracyActor);
	void ProcessHit(bool bDidHit);
	void ResetStats();
	void HitTextDisplay();
	float GetAccuracyRate() const;
	int32 GetScore() const { return score; }

private :
	int32 totalShots = 0;
	int32 hitCount = 0;
	int32 score = 0;

	UPROPERTY(VisibleAnywhere, Category = "HitManager", meta = (AllowPrivateAccess = "true"))
	ATextDisplayActor* scoreDisplayActor;

	UPROPERTY(VisibleAnywhere, Category = "HitManager", meta = (AllowPrivateAccess = "true"))
	ATextDisplayActor* accuracyDisplayActor;	

	void UpdateTextDisplays();
};
