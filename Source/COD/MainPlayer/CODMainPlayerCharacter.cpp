// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/CODMainPlayerCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACODMainPlayerCharacter::ACODMainPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ACODMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerArmMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainPlayerArmMesh"));
	// FirstPersonCamera = 

	// RootComponent = 
}

// Called every frame
void ACODMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACODMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

