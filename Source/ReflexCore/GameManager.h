// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

//추후 난이도 조정 기능 추가
UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
};

//클래스 전방 선언
class ATextDisplayActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOnBroadCast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartOnBroadCast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndOnBroadCast);

UCLASS()
class REFLEXCORE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

	void StartGame();
	void EndGame();
	void RestartGame();
	void QuitGame();

	bool IsGameActive() const { return bGameActive; }

	void InitTextActors(ATextDisplayActor* inTimerActor, ATextDisplayActor* inDifficultyActor);

	FStartOnBroadCast startOnBroadCast;
	FRestartOnBroadCast restartOnBroadCast;
	FEndOnBroadCast endOnBroadCast;

private :
	bool bGameActive = false;

	UPROPERTY(EditAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	float gameDuration = 30.f;

	float elapsedTime = 0.f;
	FTimerHandle gameTimer;

	UPROPERTY(VisibleAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	ATextDisplayActor* timerDisplayActor;
	
	UPROPERTY(VisibleAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	ATextDisplayActor* difficultyDisplayActor;

	void UpdateGameTimer();
};
