// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseTrigger.h"
#include "StoryManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APhaseTrigger::APhaseTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
	
	
}


// Called when the game starts or when spawned
void APhaseTrigger::BeginPlay()
{
	Super::BeginPlay();

	// StoryManager = Cast<AStoryManager>();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APhaseTrigger::BoxOnOverlap);

	StoryManager = Cast<AStoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStoryManager::StaticClass()));
	if (StoryManager == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Trigger : StoryManager is null"));
}

// Called every frame
void APhaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APhaseTrigger::BoxOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OverLap On"));
	if (StoryManager != nullptr)
		StoryManager->ChangePhase();
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerOverlap : StoryManager is null"));
	}
}