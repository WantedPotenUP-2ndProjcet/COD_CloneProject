// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/BulletActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassKg = 0.004f;
	V0 = 10000.f;
	GravityScale = 1.0f;
	FireAngleRad = 0.f;
	Damage = 50.f;
	DragK = 2.0e-5f;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	PrevPos = GetActorLocation();
	FVector TargetLocation = GetActorForwardVector() * 2000.f;
	FVector Direction = TargetLocation - this->GetActorLocation();
	Direction.Normalize();
	Velocity = Direction * V0;
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetBullet(DeltaTime);
	const FVector CurrPos = GetActorLocation();
	if (bDebugTrail)
	{
		DrawDebugLine(GetWorld(), PrevPos, CurrPos, TrailColor, false, TrailLifeTime, 0, 1.5f);
	}
	PrevPos = CurrPos;
}

void ABulletActor::CalcFireAngle(FVector TargetLocation)
{
	TargetLocation = GetActorForwardVector() * 2000.f;
	FVector Dir = TargetLocation - this->GetActorLocation();
	FireAngleRad = FMath::Atan2(Dir.Z, FVector2D(Dir.X, Dir.Y).Size());
	MaxRange = (V0 * V0 / 980.f) * FMath::Sin(2.f * FireAngleRad);
}

FVector ABulletActor::CalcBallistic(FVector& V, float DeltaTime)
{
	const float Speed = V.Length();
	const FVector DragAccel = (Speed > KINDA_SMALL_NUMBER)
        ? (-DragK * V * Speed) / FMath::Max(MassKg, 1e-6f)
        : FVector::ZeroVector;

	const FVector Gravity(0.f, 0.f, -980.0f * GravityScale);
	return DragAccel + Gravity;
}

void ABulletActor::SetBullet(float DeltaTime)
{
	
	const FVector CurrentPos = GetActorLocation();
    const FVector Accel = CalcBallistic(Velocity, DeltaTime);
    Velocity += Accel * DeltaTime;
    const FVector NextPos = CurrentPos + Velocity * DeltaTime;

	SetActorLocation(NextPos);
    SetActorRotation(UKismetMathLibrary::MakeRotFromX(Velocity));
}
