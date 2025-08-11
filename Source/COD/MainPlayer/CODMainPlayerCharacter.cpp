// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/CODMainPlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACODMainPlayerCharacter::ACODMainPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Movement
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

	// Camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));
	FirstPersonCamera->SetupAttachment(RootComponent);
	
	// Mesh
	FirstPersonArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArmMesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	if (CharacterMeshRef.Object)
	{
		FirstPersonArmMesh->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	FirstPersonArmMesh->SetupAttachment(FirstPersonCamera);
	
	FirstPersonArmMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/MainPlayer/Animation/ABP_MainPlayer.ABP_MainPlayer_C"));
	if (AnimInstanceClassRef.Class)
	{
		FirstPersonArmMesh->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// Input
	ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/MainPlayer/Input/IMC_MainPlayer.IMC_MainPlayer'"));
	if (InputMappingContextRef.Object)
	{
		MainPlayerMappingContext = InputMappingContextRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/IA_MainPlayerMove.IA_MainPlayerMove'"));
	if (InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> InputActionRunRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/IA_MainPlayerRun.IA_MainPlayerRun'"));
	if (InputActionRunRef.Object)
	{
		RunAction = InputActionRunRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> InputActionCrouchRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/IA_MainPlayerCrouch.IA_MainPlayerCrouch'"));
	if (InputActionCrouchRef.Object)
	{
		CrouchAction = InputActionCrouchRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/MainPlayer/Input/IA_MainPlayerLook.IA_MainPlayerLook'"));
	if (InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}
}

void ACODMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MainPlayerMappingContext, 0);
	}

	// Move
	CurrentMaxSpeed = MaxWalkSpeed;
	CurrentAcceleration = WalkAcceleration;
}

void ACODMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACODMainPlayerCharacter::Move);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ACODMainPlayerCharacter::StartRun);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ACODMainPlayerCharacter::EndRun);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ACODMainPlayerCharacter::SmoothCrouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ACODMainPlayerCharacter::SmoothUnCrouch);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACODMainPlayerCharacter::Look);
}

void ACODMainPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector MovementVector = FVector(0, 0, 0);
	MovementVector = GetActorForwardVector() * Value.Get<FVector2D>().Y + GetActorRightVector() * Value.Get<FVector2D>().X;
	MovementVector.Normalize();

	if (CurrentSpeed + CurrentAcceleration <= CurrentMaxSpeed)
	{
		CurrentSpeed += CurrentAcceleration;
	}
	else
	{
		CurrentSpeed = CurrentMaxSpeed;
	}

	FVector NextLocation = GetActorLocation();
	NextLocation = NextLocation + MovementVector * CurrentSpeed;
	
	SetActorLocation(NextLocation);
}

void ACODMainPlayerCharacter::StartRun()
{
	CurrentAcceleration = RunAcceleration;
	CurrentMaxSpeed = MaxRunSpeed;
}

void ACODMainPlayerCharacter::EndRun()
{
	CurrentAcceleration = WalkAcceleration;
	CurrentMaxSpeed = MaxWalkSpeed;
}

void ACODMainPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ACODMainPlayerCharacter::SmoothCrouch()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->Crouch();
	}
}

void ACODMainPlayerCharacter::SmoothUnCrouch()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->UnCrouch();
	}
}

