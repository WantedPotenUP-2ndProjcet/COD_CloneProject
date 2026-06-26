// Fill out your copyright notice in the Description page of Project Settings.

#include "Ally/AllyAIController.h"

#include "Ally/AllyBase_mk2.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

AAllyAIController::AAllyAIController()
{
}

void AAllyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnChar = Cast<AAllyBase_mk2>(InPawn);
	StoryManager = Cast<AStoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStoryManager::StaticClass()));

	if (StoryManager)
	{
		StoryManager->RegAICtrl(this);
	}
}

void AAllyAIController::MoveDefenseLocation(EPhase Phase)
{
	if (OwnChar == nullptr)
	{
		HasRecieved = false;
		return;
	}

	AActor* DefensePoint = nullptr;

	switch (Phase)
	{
	case EPhase::Phase1:
		DefensePoint = OwnChar->FirstDefensePoint;
		break;

	case EPhase::Phase2:
		DefensePoint = OwnChar->SecondDefensePoint;
		break;

	default:
		Standby();
		return;
	}

	if (DefensePoint == nullptr)
	{
		OwnChar->RequestEngageLoop();
		HasRecieved = false;
		return;
	}

	const FVector Destination = DefensePoint->GetActorLocation();
	OwnChar->RequestMove(Destination);

	const EPathFollowingRequestResult::Type MoveResult = MoveToLocation(Destination, OwnChar->DefenseAcceptanceRadius, false, true, false, false, nullptr, true);
	if (MoveResult == EPathFollowingRequestResult::Failed)
	{
		OwnChar->RequestEngageLoop();
		HasRecieved = false;
	}
}

void AAllyAIController::Standby()
{
	if (OwnChar)
	{
		OwnChar->RequestStandby();
	}

	HasRecieved = false;
}

void AAllyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.IsSuccess())
	{
		if (OwnChar)
		{
			OwnChar->NotifyMoveCompleted();
		}
	}

	HasRecieved = false;
}

void AAllyAIController::RecieveOrder(EPhase Phase)
{
	if (HasRecieved)
	{
		return;
	}

	HasRecieved = true;

	switch (Phase)
	{
	case EPhase::Phase1:
	case EPhase::Phase2:
		MoveDefenseLocation(Phase);
		break;

	default:
		Standby();
		break;
	}
}
