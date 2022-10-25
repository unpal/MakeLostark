// Copyright Epic Games, Inc. All Rights Reserved.

#include "testGameMode.h"
#include "testPlayerController.h"
#include "testCharacter.h"
#include "UObject/ConstructorHelpers.h"

AtestGameMode::AtestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AtestPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}