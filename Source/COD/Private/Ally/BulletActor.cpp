// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/BulletActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = 0.004f;
	V0 = 90000.f;
	Gravity = 980.f;
	FireAngleRad = 0.f;
	Damage = 50.f;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Ballistic(DeltaTime);
}

void ABulletActor::CalcFireAngle(FVector TargetLocation)
{
	FVector Dir = TargetLocation - this->GetActorLocation();
	FireAngleRad = FMath::Atan2(Dir.Z, FVector2D(Dir.X, Dir.Y).Size());
	MaxRange = (V0 * V0 / Gravity) * FMath::Sin(2.f * FireAngleRad);
}

void ABulletActor::Ballistic(float DeltaTime)
{
	const FVector CurrentPos = GetActorLocation();
    // const FVector Accel = ;
    // Velocity += Accel * DeltaTime;
    const FVector NextPos = CurrentPos + Velocity * DeltaTime;

	SetActorLocation(NextPos);
    SetActorRotation(UKismetMathLibrary::MakeRotFromX(Velocity));
}

