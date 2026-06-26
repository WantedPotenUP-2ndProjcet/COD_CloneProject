// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryManager.generated.h"

class AAIController;
class AAllyAIController;
class AAllyBase_mk2;
class USceneComponent;

struct FStoryPreviewPath
{
	FColor Color = FColor::White;
	TArray<FVector> Points;
};

UENUM(BlueprintType)
enum class EPhase : uint8
{
	Start,
	Phase1,
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

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

	EPhase CurPhase = EPhase::Start;

	UFUNCTION(BlueprintCallable)
	void ChangePhase(EPhase newphase);

	UFUNCTION(BlueprintCallable)
	void RegAICtrl(AAIController* Controller);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemyNum() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AAircraft* pAircraft;

	UFUNCTION(BlueprintCallable)
	EPhase GetPhase() const;

	UFUNCTION(CallInEditor, Category="Preview")
	void CollectAlliesInLevel();

	UFUNCTION(CallInEditor, Category="Preview")
	void RebuildPhasePreview();

	UFUNCTION(CallInEditor, Category="Preview")
	void ClearPhasePreview();

	UPROPERTY(EditAnywhere, Category="Preview")
	bool bShowPhasePreview = true;

	UPROPERTY(EditAnywhere, Category="Preview")
	bool bAutoCollectAllies = true;

	UPROPERTY(EditAnywhere, Category="Preview")
	EPhase PreviewPhase = EPhase::Phase1;

	UPROPERTY(EditAnywhere, Category="Preview", meta=(ClampMin="0.0"))
	float PreviewPathZOffset = 15.f;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
private:
	AActor* GetPreviewTargetForPhase(const AAllyBase_mk2* Ally, EPhase Phase) const;
	void HandleEditorPreviewTick();
	void DrawCachedPhasePreview() const;
	void MarkPreviewDirty();

	void StartPhase();
	void FirstPhase();
	void SecondPhase();
	void EndPhase();

	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Transient, Category="Preview")
	TArray<TObjectPtr<AAllyBase_mk2>> RegisteredAllies;

	TArray<FStoryPreviewPath> CachedPreviewPaths;

	UPROPERTY()
	TArray<TWeakObjectPtr<AAllyAIController>> AllyControllers;

	UPROPERTY()
	TArray<TWeakObjectPtr<AAIController>> EnemyControllers;

#if WITH_EDITORONLY_DATA
	bool bPreviewDirty = true;
	bool bPreviewVisibleInEditor = false;
#endif
};
