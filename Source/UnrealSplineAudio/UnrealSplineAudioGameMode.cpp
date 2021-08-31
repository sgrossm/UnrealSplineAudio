// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSplineAudioGameMode.h"
#include "UnrealSplineAudioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealSplineAudioGameMode::AUnrealSplineAudioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
