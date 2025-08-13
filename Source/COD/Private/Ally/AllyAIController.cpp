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
}

// void AAllyAIController::OnUnPosess()
// {
//     Super::OnUnPosess();
// }

void AAllyAIController::BeginToMove(const FVector& DefenseLocation, float AcceptanceRadius)
{
    
}


void AAllyAIController::OnMoveCompleted(FAIRequestID RequestID, const struct FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if(!Result.IsSuccess())
        return;
    if (Result.IsSuccess())
    {
        if (auto* Ally = Cast<AAllyCharacterBase>(GetPawn()))
        {
            Ally->OnArrivedAtPosition();
        }
    }
    
}

