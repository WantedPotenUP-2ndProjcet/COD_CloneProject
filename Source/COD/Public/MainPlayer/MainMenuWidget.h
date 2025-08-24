// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class COD_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

private:
	UPROPERTY(meta=(BindWidget))
	class UButton* StartGameBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* OptionsBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* QuitGameBtn;
};
