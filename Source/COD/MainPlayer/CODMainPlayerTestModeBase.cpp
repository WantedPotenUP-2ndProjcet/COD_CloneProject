// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/CODMainPlayerTestModeBase.h"

ACODMainPlayerTestModeBase::ACODMainPlayerTestModeBase()
{
	const ConstructorHelpers::FClassFinder<APawn> PlayerClassRef(TEXT("/Script/CoreUObject.Class'/Script/COD.CODMainPlayerCharacter'"));
	if (PlayerClassRef.Class)
	{
		DefaultPawnClass = PlayerClassRef.Class;
	}
	const ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/COD.CODMainPlayerController'"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
