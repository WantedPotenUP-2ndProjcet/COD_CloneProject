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

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// EAllyState GetState(void);
	// void SetState(EAllyState State);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(VisibleAnywhere)
	int32 MaxHP;

	UPROPERTY(VisibleAnywhere)
	int32 HP = 1.f;

	UPROPERTY(VisibleAnywhere)
	float MoveSpeed = 300.f;
	
	UPROPERTY(VisibleAnywhere)
	float AttackRange;
	
	UPROPERTY(VisibleAnywhere)
	float AttackDamage;

	UPROPERTY(VisibleAnywhere)
	float GroundFriction = 8.f;

	UPROPERTY(VisibleAnywhere, Category="AI")
	class AAIController* AIControllerPtr;
	
	UPROPERTY(VisibleAnywhere, Category="AI")
	class UBehaviorTree* BTreePtr;

	FString Name;

	// class EAllyState CurrentState;
	UPROPERTY(VisibleAnywhere, Category="FSMComponent")
	class UAllyFSM* FsmPtr;



};





