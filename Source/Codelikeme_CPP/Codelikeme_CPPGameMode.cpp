// Copyright Epic Games, Inc. All Rights Reserved.

#include "Codelikeme_CPPGameMode.h"
#include "Codelikeme_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACodelikeme_CPPGameMode::ACodelikeme_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
