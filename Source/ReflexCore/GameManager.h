// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
};

//클래스 전방 선언
class ATextDisplayActor;

UCLASS()
class REFLEXCORE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

	virtual void BeginPlay() override;

	void StartGame();
	void EndGame();
	void RestartGame();

	bool IsGameActive() const { return bGameActive; }

	void SetDifficulty(EGameDifficulty newDifficulty);
	EGameDifficulty GetDifficulty() const { return curDifficulty; }

	void InitTextActors(ATextDisplayActor* inTimerActor, ATextDisplayActor* inDifficultyActor);

private :
	bool bGameActive = false;

	EGameDifficulty curDifficulty = EGameDifficulty::Normal;

	UPROPERTY(EditAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	float gameDuration = 30.f;

	float elapsedTime = 0.f;
	FTimerHandle gameTimer;

	UPROPERTY(VisibleAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	ATextDisplayActor* timerDisplayActor;
	
	UPROPERTY(VisibleAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	ATextDisplayActor* difficultyDisplayActor;

	void UpdateGameTimer();
	void UpdateTextDisplays();
};
