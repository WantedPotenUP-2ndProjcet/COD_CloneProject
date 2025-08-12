// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/AllyFSM.h"

// Sets default values for this component's properties
UAllyFSM::UAllyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UAllyFSM::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UAllyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	switch (mState)
	{
	case EAllyState::Idle:
		IdleState();
		break;
	
		case EAllyState::Move:
		MoveState();
		break;
	
		case EAllyState::Shoot:
		ShootState();
		break;
	
		case EAllyState::Damage:
		DamageState();
		break;
	
		case EAllyState::Die:
		DieState();
		break;
	}
}

void UAllyFSM::IdleState(void)
{
	
}

void UAllyFSM::MoveState(void)
{
	
}

void UAllyFSM::ShootState(void)
{
	
}

void UAllyFSM::DamageState(void)
{
	
}

void UAllyFSM::DieState(void)
{
	
}

