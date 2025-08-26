// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/MainMenuPlayerController.h"

#include "MainPlayer/PressEnterKeyWidget.h"
#include "MainPlayer/MainMenuWidget.h"
#include "Runtime/MediaAssets/Public/MediaSource.h"
#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/MediaAssets/Public/MediaTexture.h"
#include "Components/Image.h"
#include "EnhancedInputComponent.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	ConstructorHelpers::FObjectFinder<UMediaSource> PressKeyMediaRef(TEXT("/Script/MediaAssets.FileMediaSource'/Game/MainPlayer/UI/MediaSource/MW3_Main_Touch1.MW3_Main_Touch1'"));
	if (PressKeyMediaRef.Object)
	{
		PressAnyKeyScreen1 = PressKeyMediaRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UMediaSource> PressKeyMedia2Ref(TEXT("/Script/MediaAssets.FileMediaSource'/Game/MainPlayer/UI/MediaSource/MW3_Main_Touch2.MW3_Main_Touch2'"));
	if (PressKeyMedia2Ref.Object)
	{
		PressAnyKeyScreen2 = PressKeyMedia2Ref.Object;
	}

	ConstructorHelpers::FObjectFinder<UMediaPlayer> MediaPlayer1Ref(TEXT("/Script/MediaAssets.MediaPlayer'/Game/MainPlayer/UI/MediaSource/MP_MW3_Main_Touch1.MP_MW3_Main_Touch1'"));
	if (MediaPlayer1Ref.Object)
	{
		TouchPlayer1 = MediaPlayer1Ref.Object;
	}

	ConstructorHelpers::FObjectFinder<UMediaPlayer> MediaPlayer2Ref(TEXT("/Script/MediaAssets.MediaPlayer'/Game/MainPlayer/UI/MediaSource/MP_MW3_Main_Touch2.MP_MW3_Main_Touch2'"));
	if (MediaPlayer2Ref.Object)
	{
		TouchPlayer2 = MediaPlayer2Ref.Object;
	}

	ConstructorHelpers::FObjectFinder<UMediaTexture> TouchTexture1Ref(TEXT("/Script/MediaAssets.MediaTexture'/Game/MainPlayer/UI/MediaSource/MP_MW3_Main_Touch1_Video.MP_MW3_Main_Touch1_Video'"));
	if (TouchTexture1Ref.Object)
	{
		TouchTexture1 = TouchTexture1Ref.Object;
	}

	ConstructorHelpers::FObjectFinder<UMediaTexture> TouchTexture2Ref(TEXT("/Script/MediaAssets.MediaTexture'/Game/MainPlayer/UI/MediaSource/MP_MW3_Main_Touch2_Video.MP_MW3_Main_Touch2_Video'"));
	if (TouchTexture2Ref.Object)
	{
		TouchTexture2 = TouchTexture2Ref.Object;
	}
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TouchTexture1->SetMediaPlayer(TouchPlayer1);
	TouchTexture1->UpdateResource();

	TouchTexture2->SetMediaPlayer(TouchPlayer2);
	TouchTexture2->UpdateResource();

	PressEnterKeyWidget = CreateWidget<UPressEnterKeyWidget>(GetWorld(), PressEnterKeyWidgetClass);
	PressEnterKeyWidget->AddToViewport();

	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetFactory);

	PressEnterKeyWidget->OnProceedRequested.AddLambda([this]()
		{
			if (bTransitioningToMain) return;
			bTransitioningToMain = true;

			MainMenuWidget->AddToViewport();
			PressEnterKeyWidget->RemoveFromParent();

			FInputModeUIOnly UIOnlyInputMode;
			SetInputMode(UIOnlyInputMode);
			SetShowMouseCursor(true);

			UE_LOG(LogTemp, Warning, TEXT("Transition to Main Menu!"));
		});

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	SetShowMouseCursor(false);

	TouchPlayer1->OpenSource(PressAnyKeyScreen1);
	TouchPlayer1->OnEndReached.AddUniqueDynamic(this, &AMainMenuPlayerController::OnIntroEnd);

	TouchPlayer2->OnMediaOpened.AddUniqueDynamic(this, &AMainMenuPlayerController::OnLoopBegin);
	TouchPlayer2->OpenSource(PressAnyKeyScreen2);

}

void AMainMenuPlayerController::OnIntroEnd()
{
	TouchPlayer2->Play();
	PressEnterKeyWidget->PressEnterKeyImage1->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuPlayerController::OnLoopBegin(FString OpenedURL)
{
	TouchPlayer2->Pause();
	TouchPlayer2->Seek(FTimespan::Zero());
}
