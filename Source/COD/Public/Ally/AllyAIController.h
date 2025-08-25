
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StoryManager.h"
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
    void MoveDefenseLocation();
	
    // 이동 완료 콜백
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void RecieveOrder(EPhase Phase);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AStoryManager* StoryManager;

private:
    class AAllyCharacterBase * OwnChar;

	bool HasRecieved = false;
    
};
