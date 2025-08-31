// Fill out your copyright notice in the Description page of Project Settings.


#include "Aircraft.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AAircraft::AAircraft()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
}

// Called when the game starts or when spawned
void AAircraft::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetVisibility(false);

	InitLoc = GetActorLocation();
}

// Called every frame
void AAircraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAircraft::AirStrike()
{
	UE_LOG(LogTemp, Warning, TEXT("AirStrike incomming"));
	SetActorTickEnabled(true);
	Mesh->SetVisibility(true);
}

