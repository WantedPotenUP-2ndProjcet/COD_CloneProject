// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/WeaponBase.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Ally/BulletActor.h"
#include "Ally/AllyCharacterBase.h"
#include "Components/ArrowComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	Mesh->SetRelativeScale3D(FVector(3.f, 3.5f, 3.f));

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);
	Muzzle->SetRelativeLocation(FVector(0.f, 60.f, 6.f));
	Muzzle->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
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

AController* AWeaponBase::GetOwnerController() const
{
	AAllyCharacterBase* OwnerChar = Cast<AAllyCharacterBase>(GetOwner());

	if(OwnerChar == nullptr)
		return nullptr;
	
	return OwnerChar->GetController();
}

void AWeaponBase::SpawnBullet()
{
	FTransform t = Muzzle->GetComponentTransform();
    GetWorld()->SpawnActor<ABulletActor>(BulletClass, t);
}

void AWeaponBase::PullTrigger(void)
{
	if(GEngine)
	{
		const FString CurFunc = ANSI_TO_TCHAR(__FUNCTION__);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, CurFunc);
	}
	// Need mesh socket effect attact
	SpawnBullet();
}

