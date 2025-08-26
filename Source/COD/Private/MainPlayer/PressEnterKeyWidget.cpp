// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/PressEnterKeyWidget.h"

#include "MainPlayer/MainMenuPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UPressEnterKeyWidget::UPressEnterKeyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UInputMappingContext> MainMenuMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MainPlayer/Input/IMC_PressEnterKeyToMain.IMC_PressEnterKeyToMain'"));
	if (MainMenuMappingContextRef.Object)
	{
		PressEnterKeyMappingContext = MainMenuMappingContextRef.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> PressEnterKeyActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/MainMenu/IA_PressEnterToMain.IA_PressEnterToMain'"));
	if (PressEnterKeyActionRef.Object)
	{
		PressEnterKeyAction = PressEnterKeyActionRef.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> PressSpaceKeyActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/MainMenu/IA_PressSpaceToMain.IA_PressSpaceToMain'"));
	if (PressSpaceKeyActionRef.Object)
	{
		PressSpaceKeyAction = PressSpaceKeyActionRef.Object;
	}
	ConstructorHelpers::FObjectFinder<UInputAction> ClickMouseActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/MainMenu/IA_ClickMouseToMain.IA_ClickMouseToMain'"));
	if (ClickMouseActionRef.Object)
	{
		ClickMouseAction = ClickMouseActionRef.Object;
	}
}

void UPressEnterKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (auto* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayer()->GetLocalPlayer()))
	{
		Sub->AddMappingContext(PressEnterKeyMappingContext, 0);

		if (UEnhancedInputComponent* enhancedInput = CastChecked<UEnhancedInputComponent>(GetOwningPlayer()->InputComponent))
		{
			enhancedInput->BindAction(PressEnterKeyAction, ETriggerEvent::Started, this, &UPressEnterKeyWidget::PressEnterKey);
			enhancedInput->BindAction(ClickMouseAction, ETriggerEvent::Started, this, &UPressEnterKeyWidget::PressEnterKey);
		}
	}
}

void UPressEnterKeyWidget::PressEnterKey(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter Key is Pressed!"));
	OnProceedRequested.Broadcast();
}