// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputAction.h"
#include "PressEnterKeyWidget.generated.h"

/**
 *
 */

DECLARE_MULTICAST_DELEGATE(FOnProceedRequested);

UCLASS()
class COD_API UPressEnterKeyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPressEnterKeyWidget(const FObjectInitializer& ObjectInitializer);

	FOnProceedRequested OnProceedRequested;	// For MainMenuPlayerController

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
	void PressEnterKey(const FInputActionValue& Value);

	UPROPERTY()
	TObjectPtr<class UInputMappingContext> PressEnterKeyMappingContext;

	UPROPERTY()
	TObjectPtr<class UInputAction> PressEnterKeyAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> PressSpaceKeyAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> ClickMouseAction;

	UPROPERTY(meta=(BindWidget))
	class UImage* PressEnterKeyImage1;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* PressEnterKeyImage2;

};
