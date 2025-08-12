// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AllyFSM.generated.h"


UENUM(BlueprintType)
enum class EAllyState : uint8
{
	Idle UMETA(DisplayName="Idle"),
	Move UMETA(DisplayName="Move"),
	Shoot UMETA(DisplayName="Shoot"),
	Damage UMETA(DisplayName="Damage"),
	Die UMETA(DisplayName="Die")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COD_API UAllyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAllyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM")
	EAllyState mState = EAllyState::Idle;	// default

	void IdleState(void);
	void MoveState(void);
	void ShootState(void);
	void DamageState(void);
	void DieState(void);
};
