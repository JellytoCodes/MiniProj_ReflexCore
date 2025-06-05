// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReflexCoreGameMode.h"
#include "ReflexCoreCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReflexCoreGameMode::AReflexCoreGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
