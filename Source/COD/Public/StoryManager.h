// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryManager.generated.h"

UENUM(BlueprintType)
enum class EPhase : uint8
{
	Start,
	Phase2,
	Ending
};

UCLASS()
class COD_API AStoryManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoryManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EPhase CurPhase = EPhase::Start;

	// UFUNCTION(BlueprintCallable)
	void ChangePhase(EPhase NewPhase);

private:
	void StartPhase();
	void SecondPhase();
	void EndPhase();
};
