// Fill out your copyright notice in the Description page of Project Settings.

#include "StoryManager.h"

#include "Aircraft.h"
#include "AIController.h"
#include "Ally/AllyAIController.h"
#include "Ally/AllyBase_mk2.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

AStoryManager::AStoryManager()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
}

void AStoryManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (IsTemplate())
		return;

	if (bAutoCollectAllies)
		CollectAlliesInLevel();

	MarkPreviewDirty();
	HandleEditorPreviewTick();
}

void AStoryManager::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoCollectAllies)
		CollectAlliesInLevel();

	ClearPhasePreview();
	ChangePhase(EPhase::Start);
}

void AStoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleEditorPreviewTick();
}

bool AStoryManager::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AStoryManager::CollectAlliesInLevel()
{
	RegisteredAllies.Reset();

	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	for (TActorIterator<AAllyBase_mk2> It(World); It; ++It)
	{
		AAllyBase_mk2* Ally = *It;
		if (IsValid(Ally))
			RegisteredAllies.Add(Ally);
	}

	MarkPreviewDirty();
}

void AStoryManager::RebuildPhasePreview()
{
	ClearPhasePreview();

	UWorld* World = GetWorld();
	if (World == nullptr || IsTemplate() || !bShowPhasePreview)
	{
		MarkPreviewDirty();
		return;
	}

	if (bAutoCollectAllies)
		CollectAlliesInLevel();

	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (NavigationSystem == nullptr)
	{
		MarkPreviewDirty();
		return;
	}

	FLinearColor PreviewColor = FLinearColor(0.1f, 0.85f, 1.f);
	if (PreviewPhase == EPhase::Phase2)
	{
		PreviewColor = FLinearColor(1.f, 0.45f, 0.05f);
	}

	for (AAllyBase_mk2* Ally : RegisteredAllies)
	{
		if (!IsValid(Ally))
			continue;

		AActor* TargetActor = GetPreviewTargetForPhase(Ally, PreviewPhase);
		if (!IsValid(TargetActor))
			continue;

		FVector PathStart = Ally->GetActorLocation();
		FVector PathEnd = TargetActor->GetActorLocation();

		FNavLocation ProjectedStart;
		if (NavigationSystem->ProjectPointToNavigation(PathStart, ProjectedStart))
			PathStart = ProjectedStart.Location;

		FNavLocation ProjectedEnd;
		if (NavigationSystem->ProjectPointToNavigation(PathEnd, ProjectedEnd))
			PathEnd = ProjectedEnd.Location;

		UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, PathStart, PathEnd, Ally);
		if (NavigationPath == nullptr || !NavigationPath->IsValid() || NavigationPath->PathPoints.Num() < 2)
			continue;

		FStoryPreviewPath& CachedPath = CachedPreviewPaths.AddDefaulted_GetRef();
		CachedPath.Color = PreviewColor.ToFColor(true);
		CachedPath.Points.Reserve(NavigationPath->PathPoints.Num());

		for (const FVector& PathPoint : NavigationPath->PathPoints)
		{
			const FVector PreviewPoint = PathPoint + FVector(0.f, 0.f, PreviewPathZOffset);
			CachedPath.Points.Add(PreviewPoint);
		}
	}

#if WITH_EDITORONLY_DATA
	bPreviewDirty = false;
	bPreviewVisibleInEditor = true;
#endif
}

void AStoryManager::ClearPhasePreview()
{
	CachedPreviewPaths.Reset();

#if WITH_EDITORONLY_DATA
	bPreviewVisibleInEditor = false;
#endif
}

EPhase AStoryManager::GetPhase() const
{
	return CurPhase;
}

void AStoryManager::StartPhase()
{
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Start);
}

void AStoryManager::FirstPhase()
{
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Phase1);
}

void AStoryManager::SecondPhase()
{
	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Phase2);
		
}

void AStoryManager::EndPhase()
{
	UE_LOG(LogTemp, Warning, TEXT("End Phase!"));

	for (TWeakObjectPtr<AAllyAIController> Elem : AllyControllers)
		Elem->RecieveOrder(EPhase::Ending);

	if (pAircraft != nullptr)
		pAircraft->AirStrike();
}

void AStoryManager::ChangePhase(EPhase newphase)
{
	CurPhase = newphase;
	switch (CurPhase)
	{
		case EPhase::Start:
			{
				StartPhase();
				break;
			}

		case EPhase::Phase1:
			{
				FirstPhase();
				break;
			}
			
		case EPhase::Phase2:
			{
				SecondPhase();
				break;
			}
		case EPhase::Ending :
			{
				EndPhase();
				break;
			}
	}
}

void AStoryManager::RegAICtrl(AAIController* Controller)
{
	if (Controller == nullptr)
		return;

	if (IsValid(Cast<AAllyAIController>(Controller)))
		AllyControllers.Add(Cast<AAllyAIController>(Controller));

	else if (IsValid(Controller))
		EnemyControllers.Add(Controller);
}

int32 AStoryManager::GetEnemyNum() const
{
	return EnemyControllers.Num();
}

AActor* AStoryManager::GetPreviewTargetForPhase(const AAllyBase_mk2* Ally, EPhase Phase) const
{
	if (!IsValid(Ally))
		return nullptr;

	switch (Phase)
	{
	case EPhase::Phase1:
		return Ally->FirstDefensePoint;

	case EPhase::Phase2:
		return Ally->SecondDefensePoint;

	default:
		return nullptr;
	}
}

void AStoryManager::HandleEditorPreviewTick()
{
#if WITH_EDITOR
	UWorld* World = GetWorld();
	if (!GIsEditor || World == nullptr || World->IsGameWorld() || IsTemplate())
		return;

	if (!bShowPhasePreview)
	{
		if (bPreviewVisibleInEditor || CachedPreviewPaths.Num() > 0)
			ClearPhasePreview();

		return;
	}

	if (bPreviewDirty || !bPreviewVisibleInEditor)
		RebuildPhasePreview();

	DrawCachedPhasePreview();
#endif
}

void AStoryManager::DrawCachedPhasePreview() const
{
#if WITH_EDITOR
	UWorld* World = GetWorld();
	if (World == nullptr || World->IsGameWorld())
		return;

	for (const FStoryPreviewPath& CachedPath : CachedPreviewPaths)
	{
		const int32 NumPoints = CachedPath.Points.Num();
		for (int32 PointIndex = 0; PointIndex + 1 < NumPoints; ++PointIndex)
		{
			DrawDebugLine(World, CachedPath.Points[PointIndex], CachedPath.Points[PointIndex + 1], CachedPath.Color, false, 0.f, 0, 6.f);
		}
	}
#endif
}

void AStoryManager::MarkPreviewDirty()
{
#if WITH_EDITORONLY_DATA
	bPreviewDirty = true;
#endif
}

#if WITH_EDITOR
void AStoryManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (IsTemplate())
		return;

	if (bAutoCollectAllies)
		CollectAlliesInLevel();

	MarkPreviewDirty();
	HandleEditorPreviewTick();
}
#endif
