// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "TextDisplayActor.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGameManager::StartGame()
{
	if(bGameActive) return;

	bGameActive = true;
	elapsedTime = 0.f;

	startOnBroadCast.Broadcast();

	GetWorldTimerManager().SetTimer(gameTimer, this, &AGameManager::UpdateGameTimer, 1.f, true);
}

void AGameManager::EndGame()
{
	bGameActive = false;

	endOnBroadCast.Broadcast();

	GetWorldTimerManager().ClearTimer(gameTimer);
}

void AGameManager::RestartGame()
{
	EndGame();
	StartGame();
}

void AGameManager::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void AGameManager::InitTextActors(ATextDisplayActor *inTimerActor, ATextDisplayActor *inDifficultyActor)
{
	timerDisplayActor = inTimerActor;
	difficultyDisplayActor = inDifficultyActor;
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

