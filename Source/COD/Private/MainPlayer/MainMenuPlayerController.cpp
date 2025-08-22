// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/MainMenuPlayerController.h"

#include "MainPlayer/MainMenuWidget.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainWidgetFactory);
	MainWidget->AddToViewport();

	ConstructorHelpers::FObjectFinder<UMediaSource> PressKeyMediaRef(TEXT("/Script/MediaAssets.FileMediaSource'/Game/MainPlayer/UI/MediaSource/MW3_Main_Touch1.MW3_Main_Touch1'"));
	if (PressKeyMediaRef.Object)
	{
		PressAnyKeyScreen = PressKeyMediaRef.Object;
	}
	PressAnyKeyScreen->OpenSource();
}
