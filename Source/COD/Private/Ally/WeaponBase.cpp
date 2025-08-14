// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AWeaponBase::OnFire(void)
{
	if(GEngine)
	{
		const FString CurFunc = ANSI_TO_TCHAR(__FUNCTION__);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, CurFunc);
	}
}

