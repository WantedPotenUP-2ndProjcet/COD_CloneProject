
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
    void MoveDefenseLocation(const FVector& DefenseLocation, float Acceptance);
	
    // 이동 완료 콜백
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
    

private:
    class AAllyCharacterBase * p_OwnChar;

    void RecieveOrder();
    
};
