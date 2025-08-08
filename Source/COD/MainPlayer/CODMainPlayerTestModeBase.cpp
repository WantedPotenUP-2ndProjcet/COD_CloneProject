// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/CODMainPlayerTestModeBase.h"

ACODMainPlayerTestModeBase::ACODMainPlayerTestModeBase()
{
	const ConstructorHelpers::FClassFinder<APawn> PlayerClassRef(TEXT("/Game/MainPlayer/Character/BP_MainPlayerCharacter.BP_MainPlayerCharacter_C"));
	if (PlayerClassRef.Class)
	{
		DefaultPawnClass = PlayerClassRef.Class;
	}
	const ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/MainPlayer/Character/BP_MainPlayerController.BP_MainPlayerController_C"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
