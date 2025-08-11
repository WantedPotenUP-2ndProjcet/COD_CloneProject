// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AllyCharacterBase.generated.h"

UCLASS()
class COD_API AAllyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAllyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	int32 MaxHP;
	int32 CurrentHP = 1.f;
	float MaxMoveSpeed = 300.f;
	float GroundFriction = 8.f;
	float MaxAcceleration = 2048.f;
	float BrakingDeceleration = 2048.f;
	FRotator RotationRate = FRotator(0.f, 720.f, 0.f);
	class EAllyState CurrentState;

	void SetState(class EAllyState State);
	class EAllyState GetState(void);
	void ChangeState(void);
	void ChangeState(class EAllyState State);
};





