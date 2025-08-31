// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryManager.h"
#include "Aircraft.h"
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

	ChangePhase(EPhase::Start);
}

// Called every frame
void AStoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoryManager::StartPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Game"));
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Start);
}

void AStoryManager::FirstPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("First Phase!"));
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Phase1);
}

void AStoryManager::SecondPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("2nd Phase!"));
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Phase2);
		
}

void AStoryManager::EndPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("End Phase!"));
	if (!ensure(pAircraft != nullptr))
		UE_LOG(LogTemp, Error, TEXT("pAircraft NULL"));

	pAircraft->AirStrike();
}

void AStoryManager::ChangePhase(EPhase newphase)
{
	CurPhase = newphase;
	switch (CurPhase)
	{
		case EPhase::Phase1:
			{
				FirstPhase();
				break;
			}
			
		case EPhase::Phase2:
			{
				SecondPhase();
				break;
			}
		case EPhase::Ending :
			{
				EndPhase();
			}
	}
}

void AStoryManager::RegAICtrl(AAIController* Controller)
{
	if (Controller == nullptr)
		return;

	if (IsValid(Cast<AAllyAIController>(Controller)))
		AllyControllers.Add(Cast<AAllyAIController>(Controller));

	else if (IsValid(Controller))
		EnemyControllers.Add(Controller);
}

int32 AStoryManager::GetEnemyNum() const
{
	return EnemyControllers.Num();
}
