// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/AllyAIController.h"
#include "Ally/AllyCharacterBase.h"
#include "Navigation/PathFollowingComponent.h"

AAllyAIController::AAllyAIController()
{
    // bAttachToPawn = true;
    
}

void AAllyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    p_OwnChar = Cast<AAllyCharacterBase>(GetPawn());
}

void AAllyAIController::MoveDefenseLocation(const FVector& DefenseLocation, float Acceptance)
{
    if(p_OwnChar != nullptr)
    {
        p_OwnChar->SetState(EAllyState::Move);
        MoveToLocation(DefenseLocation, Acceptance, false, true, false, false, nullptr, true);
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
        if (p_OwnChar)
        {
            p_OwnChar->OnArrivedAtPosition();
        }
    }
    
}

void AAllyAIController::RecieveOrder()
{
    
}

