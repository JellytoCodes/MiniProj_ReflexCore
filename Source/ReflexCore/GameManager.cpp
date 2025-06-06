// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "TextDisplayActor.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle loadTimer;
	GetWorldTimerManager().SetTimer(loadTimer, [&]
	{
		UpdateTextDisplays();
	}, .1f, false);
}

void AGameManager::StartGame()
{
	if(bGameActive) return;

	bGameActive = true;
	elapsedTime = 0.f;

	GetWorldTimerManager().SetTimer(gameTimer, this, &AGameManager::UpdateGameTimer, 1.f, true);

	UE_LOG(LogTemp, Warning, TEXT("Game Started"));
}

void AGameManager::EndGame()
{
	bGameActive = false;
	GetWorldTimerManager().ClearTimer(gameTimer);

	UE_LOG(LogTemp, Warning, TEXT("Game Ended"));
}

void AGameManager::RestartGame()
{
	EndGame();
	StartGame();
}

void AGameManager::SetDifficulty(EGameDifficulty newDifficulty)
{
	curDifficulty = newDifficulty;
	UpdateTextDisplays();
}

void AGameManager::InitTextActors(ATextDisplayActor *inTimerActor, ATextDisplayActor *inDifficultyActor)
{
	timerDisplayActor = inTimerActor;
	difficultyDisplayActor = inDifficultyActor;
	UpdateTextDisplays();
}

void AGameManager::UpdateGameTimer()
{
	if(!bGameActive) return;

	elapsedTime += 1.f;
	float remainTime = FMath::Clamp(gameDuration - elapsedTime, 0.f, gameDuration);
	
	if(timerDisplayActor)
	{
		timerDisplayActor->UpdateDisplayValue(remainTime);
	}

	if(remainTime <= 0.f) EndGame();
}

void AGameManager::UpdateTextDisplays()
{
	if(difficultyDisplayActor)
	{
		FString diffName;

		switch(curDifficulty)
		{
			case EGameDifficulty::Easy :
				diffName = "Easy";
			break;
			case EGameDifficulty::Normal :
				diffName = "Normal";
			break;

			case EGameDifficulty::Hard :
				diffName = "Hard";
			break;
		}
		difficultyDisplayActor->UpdateDisplayValue((float)curDifficulty);
	}
}

