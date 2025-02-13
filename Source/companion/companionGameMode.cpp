// Copyright Epic Games, Inc. All Rights Reserved.

#include "companionGameMode.h"
#include "companionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AcompanionGameMode::AcompanionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
