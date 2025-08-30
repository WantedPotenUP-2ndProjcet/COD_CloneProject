// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryManager.h"
#include "PhaseTrigger.generated.h"

UCLASS()
class COD_API APhaseTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APhaseTrigger();

	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;
	
	UPROPERTY(EditAnywhere)
	class AStoryManager * StoryManager = nullptr;
	
	UPROPERTY(EditAnywhere)
	EPhase ToPhase;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void BoxOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:
	
};
