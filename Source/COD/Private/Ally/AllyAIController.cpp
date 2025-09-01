// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/AllyAIController.h"
#include "Ally/AllyCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

AAllyAIController::AAllyAIController()
{
    // bAttachToPawn = true;
    
}

void AAllyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    OwnChar = Cast<AAllyCharacterBase>(GetPawn());
    StoryManager = Cast<AStoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AStoryManager::StaticClass()));
    if (StoryManager)
        StoryManager->RegAICtrl(this);
}

void AAllyAIController::MoveDefenseLocation()
{
    if(OwnChar != nullptr)
    {
        if (StoryManager->CurPhase == EPhase::Phase1)
        {
            if (OwnChar->FirstDefensePoint != nullptr )
            {
                FVector DefenseLocation = OwnChar->FirstDefensePoint->GetActorLocation();
                OwnChar->SetState(EAllyState::Move);
                MoveToLocation(DefenseLocation, OwnChar->DefenseAcceptanceRadius, false, true, false, false, nullptr, true);
            }
        }
        else if (StoryManager->CurPhase == EPhase::Phase2)
        {
            if (OwnChar->SecondDefensePoint != nullptr )
            {
                FVector DefenseLocation = OwnChar->SecondDefensePoint->GetActorLocation();
                OwnChar->SetState(EAllyState::Move);
                MoveToLocation(DefenseLocation, OwnChar->DefenseAcceptanceRadius, false, true, false, false, nullptr, true);
            }
        }
    }
}

void AAllyAIController::Standby()
{
    OwnChar->SetState(EAllyState::Ready);
}

// void AAllyAIController::OnUnPosess()
// {
//     Super::OnUnPosess();
// }

void AAllyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

   // if(!Result.IsSuccess())
   //     UE_LOG(LogTemp, Error, TEXT("Not Arrived"));
    if (Result.IsSuccess())
    {
        if (OwnChar)
        {
            OwnChar->OnArrivedAtPosition();
        }
    }

    HasRecieved = false;
}

void AAllyAIController::RecieveOrder(EPhase Phase)
{
    if (HasRecieved == true)
        return;

    if (Phase == EPhase::Start)
    {
        HasRecieved = true;
        
    }

    if (Phase == EPhase::Phase1)
    {
        HasRecieved = true;
        MoveDefenseLocation();
    }
    
    if (Phase == EPhase::Phase2)
    {
        HasRecieved = true;
        MoveDefenseLocation();
    }
}


