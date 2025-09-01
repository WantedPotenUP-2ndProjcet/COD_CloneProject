// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/WeaponBase.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Ally/BulletActor.h"
#include "Ally/AllyCharacterBase.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

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

	ConstructorHelpers::FClassFinder<ABulletActor> tmpBullet(TEXT("/Script/Engine.Blueprint'/Game/Ally/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (tmpBullet.Succeeded())
		BulletClass = tmpBullet.Class;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AAllyCharacterBase>(GetOwner());
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

UNiagaraComponent* AWeaponBase::PlayMuzzleVFX(bool bAttach)
{
	if (!MuzzleVFX) return nullptr;

	const FTransform Xf = Muzzle->GetComponentTransform();
	UNiagaraComponent* Comp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		MuzzleVFX,
		Xf.GetLocation(),
		Xf.Rotator(),
		FVector(1.f),
		/*bAutoDestroy=*/true,
		/*bAutoActivate=*/true,
		ENCPoolMethod::AutoRelease,
		/*bPreCullCheck=*/true
	);
	return Comp;
}

AController* AWeaponBase::GetOwnerController() const
{
	if(!ensure(Owner != nullptr))
	{
		return nullptr;
	}
	return Owner->GetController();
}


void AWeaponBase::PullTrigger()
{
	/*if(GEngine)
	{
		FString CurFunc = ANSI_TO_TCHAR(__FUNCTION__);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, CurFunc);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, GetName());
		UE_LOG(LogTemp, Warning, TEXT("PullTrigger"));
	}*/
	
	SpawnBullet();
	PlayMuzzleVFX(false);
	if (muzzleSFX != nullptr)
		UGameplayStatics::PlaySound2D(GetWorld(), muzzleSFX);
}

void AWeaponBase::SpawnBullet()
{
	FTransform t = Muzzle->GetComponentTransform();
    Bullet = GetWorld()->SpawnActor<ABulletActor>(BulletClass, t);
	//if (!IsValid(Bullet))
	//	UE_LOG(LogTemp, Error, TEXT("WeaponBase::Bullet NULL"));
}
