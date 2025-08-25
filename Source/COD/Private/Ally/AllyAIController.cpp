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
        
        if (OwnChar->DefensePoint != nullptr )
        {
            FVector DefenseLocation = OwnChar->DefensePoint->GetActorLocation();
            OwnChar->SetState(EAllyState::Move);
            MoveToLocation(DefenseLocation, OwnChar->DefenseAcceptanceRadius, false, true, false, false, nullptr, true);
        }
    }
}

// void AAllyAIController::OnUnPosess()
// {
//     Super::OnUnPosess();
// }

void AAllyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if(!Result.IsSuccess())
        return;
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
    
    if (Phase == EPhase::Phase2)
    {
        MoveDefenseLocation();
        HasRecieved = true;
    }
}


