// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/AllyCharacterBase.h"
#include "Ally/EAllyState.h"

// Sets default values
AAllyCharacterBase::AAllyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAllyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAllyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAllyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAllyCharacterBase::SetState(class EAllyState State)
{
	CurrentState = State;
}

class EAllyState AAllyCharacterBase::GetState(void)
{
	return CurrentState;
}

void AAllyCharacterBase::ChangeState(class EAllyState State)
{
	
}