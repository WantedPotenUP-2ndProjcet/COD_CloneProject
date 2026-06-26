#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StoryManager.h"
#include "AllyAIController.generated.h"

class AAllyBase_mk2;

UCLASS()
class COD_API AAllyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAllyAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	void MoveDefenseLocation(EPhase Phase);

	UFUNCTION(BlueprintCallable)
	void Standby();
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void RecieveOrder(EPhase Phase);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AStoryManager* StoryManager;

private:
	TObjectPtr<AAllyBase_mk2> OwnChar = nullptr;

	bool HasRecieved = false;
};
