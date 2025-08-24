// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryManager.h"

// Sets default values
AStoryManager::AStoryManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStoryManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurPhase)
	{
		case EPhase::Start:
			StartPhase();
			break;

		case EPhase::Phase2:
			SecondPhase();
			break;

		case EPhase::Ending:
			EndPhase();
			break;
	}

}

void AStoryManager::StartPhase()
{
	
}

void AStoryManager::SecondPhase()
{
	
}

void AStoryManager::EndPhase()
{
	
}

void AStoryManager::ChangePhase(EPhase NewPhase)
{
	CurPhase = NewPhase;
}

