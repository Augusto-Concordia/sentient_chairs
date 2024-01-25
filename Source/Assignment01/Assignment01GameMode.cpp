// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment01GameMode.h"
#include "Assignment01Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment01GameMode::AAssignment01GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
