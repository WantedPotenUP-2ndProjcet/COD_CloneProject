// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "CODMainPlayerCharacter.generated.h"

UCLASS()
class COD_API ACODMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACODMainPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override; 

// Character Section
protected:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<class UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonArmMesh;

// Input Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> MainPlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	void Move(const FInputActionValue& Value);
	void StartRun();
	void EndRun();
	void Look(const FInputActionValue& Value);
	void SmoothCrouch();
	void SmoothUnCrouch();

private:
	const float MaxWalkSpeed = 10.0f;
	const float WalkAcceleration = 0.2f;
	const float MaxAimingSpeed = 2.0f;
	const float MaxCrouchSpeed = 2.0f;
	const float CrouchAcceleration = 10.0f;
	const float MaxRunSpeed = 20.0f;
	const float RunAcceleration = 0.4f;

	float CurrentSpeed = 0.0f;
	float CurrentAcceleration = 0.0f;
	float CurrentMaxSpeed = 0.0f;
};
