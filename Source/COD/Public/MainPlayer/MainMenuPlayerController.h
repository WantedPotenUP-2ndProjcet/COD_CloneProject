// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */



UCLASS()
class COD_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnIntroEnd();

	UFUNCTION()
	void OnLoopBegin(FString OpenedURL);

private:
	// About Bool
	UPROPERTY()
	bool bTransitioningToMain = false;


	// About Widget Classes
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPressEnterKeyWidget> PressEnterKeyWidgetClass;

	UPROPERTY()
	TObjectPtr<class UPressEnterKeyWidget> PressEnterKeyWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetFactory;

	UPROPERTY()
	TObjectPtr<class UMainMenuWidget> MainMenuWidget;

	// About Press Enter Key Widget
	UPROPERTY(EditAnywhere)
	class UMediaPlayer* TouchPlayer1;

	UPROPERTY(EditAnywhere)
	class UMediaPlayer* TouchPlayer2;

	UPROPERTY()
	class UMediaTexture* TouchTexture1;

	UPROPERTY()
	class UMediaTexture* TouchTexture2;

	UPROPERTY()
	class UMediaSource* PressAnyKeyScreen1;

	UPROPERTY()
	class UMediaSource* PressAnyKeyScreen2;
};
