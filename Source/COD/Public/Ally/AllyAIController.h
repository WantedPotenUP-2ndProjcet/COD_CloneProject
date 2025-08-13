
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AllyAIController.generated.h"

/**
 * 
 */
class AAllyCharacterBase;
UCLASS()
class COD_API AAllyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    AAllyAIController();

    virtual void OnPossess(APawn* InPawn) override;
	// virtual void OnUnPosess() override;

	UFUNCTION(BlueprintCallable)
	void BeginToMove(const FVector& DefenseLocation, float AcceptanceRadius = 75.f);
    // 이동 완료 콜백
    virtual void OnMoveCompleted(FAIRequestID RequestID, const struct FPathFollowingResult& Result) override;

};
