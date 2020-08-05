// Copyright Epic Games, Inc. All Rights Reserved.

#include "ATP_ProjectGameMode.h"
#include "ATP_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AATP_ProjectGameMode::AATP_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
