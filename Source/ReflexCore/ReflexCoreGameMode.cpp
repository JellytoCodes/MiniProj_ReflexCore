// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReflexCoreGameMode.h"
#include "ReflexCoreCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.h"
#include "TextDisplayActor.h"

AReflexCoreGameMode::AReflexCoreGameMode() : Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AReflexCoreGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATextDisplayActor::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		ATextDisplayActor* TextActor = Cast<ATextDisplayActor>(Actor);
		if (TextActor && TextActor->GetDisplayCategory() == ETextDisplayCategory::timer)
		{
			timerDisplayActor = TextActor;
		}
		else if (TextActor && TextActor->GetDisplayCategory() == ETextDisplayCategory::difficulty)
		{
			difficultyDisplayActor = TextActor;
		}
	}

	gameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	if(gameManager) gameManager->InitTextActors(timerDisplayActor, difficultyDisplayActor);
	else UE_LOG(LogTemp, Warning, TEXT("Failed Log"));
}
