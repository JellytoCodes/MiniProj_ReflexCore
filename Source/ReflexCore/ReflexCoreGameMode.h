// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ReflexCoreGameMode.generated.h"

UCLASS(minimalapi)
class AReflexCoreGameMode : public AGameModeBase
{
	GENERATED_BODY()

public :
	AReflexCoreGameMode();

	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

private :
	UPROPERTY(VisibleAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	class ATextDisplayActor* timerDisplayActor;
	
	UPROPERTY(VisibleAnywhere, Category = "GameManager", meta = (AllowPrivateAccess = "true"))
	class ATextDisplayActor* difficultyDisplayActor;

	class AGameManager* gameManager;

public :
	FORCEINLINE AGameManager* GetGameManager() { return gameManager; }
	
};



