// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/WeaponBase.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeaponBase::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr)
		return false;

	FVector Location = FVector(0);
	FRotator Rotation = FRotator(0);

	// 플레이어 좌표 수신
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return false;
}

AController* AWeaponBase::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if(OwnerPawn == nullptr)
		return nullptr;
	
	return OwnerPawn->GetController();
}

void AWeaponBase::PullTrigger(void)
{
	if(GEngine)
	{
		const FString CurFunc = ANSI_TO_TCHAR(__FUNCTION__);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, CurFunc);
	}
	// Need mesh socket effect attact

	// LineTrace
	FVector ShotDirection = FVector(0);
	FHitResult HitResult;
}

