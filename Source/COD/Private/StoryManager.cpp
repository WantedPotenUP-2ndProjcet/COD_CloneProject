// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryManager.h"

#include "Ally/AllyAIController.h"

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

	CurPhase = EPhase::Start;
	UE_LOG(LogTemp, Warning, TEXT("1st Phase On!"));
}

// Called every frame
void AStoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoryManager::StartPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("1st Phase On!"));
}

void AStoryManager::SecondPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("2nd Phase On!"));
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Phase2);
		
}

void AStoryManager::EndPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("End Phase On!"));
}

void AStoryManager::ChangePhase()
{
	if (CurPhase == EPhase::Start)
	{
		CurPhase = EPhase::Phase2;
		SecondPhase();
	}

	else if (CurPhase == EPhase::Phase2)
	{
		CurPhase = EPhase::Ending;
		EndPhase();
	}

	else
	{
		return;
	}
}

void AStoryManager::RegAICtrl(AAIController* Controller)
{
	if (Controller == nullptr)
		return;

	if (IsValid(Cast<AAllyAIController>(Controller)))
		AllyControllers.Add(Cast<AAllyAIController>(Controller));

	else
		EnemyControllers.Add(Controller);
}
