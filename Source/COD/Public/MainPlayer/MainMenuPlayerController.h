// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COD_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenuWidget> MainWidgetFactory;

	UPROPERTY()
	class UMainMenuWidget* MainWidget;

	UPROPERTY()
	class UMediaSource* PressAnyKeyScreen;
};
