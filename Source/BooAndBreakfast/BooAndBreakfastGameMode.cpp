// Copyright Epic Games, Inc. All Rights Reserved.

#include "BooAndBreakfastGameMode.h"
#include "BooAndBreakfastCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABooAndBreakfastGameMode::ABooAndBreakfastGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
