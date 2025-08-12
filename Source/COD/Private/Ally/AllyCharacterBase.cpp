// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/AllyCharacterBase.h"
#include "Ally/AllyFSM.h"

// Sets default values
AAllyCharacterBase::AAllyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FsmPtr = CreateDefaultSubobject<UAllyFSM>(TEXT("FSM"));

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
