// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally/BulletActor.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	
	PrevPos = FVector(0);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	PrevPos = GetActorLocation();
	Velocity = GetActorForwardVector() * BulletSpeed;
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetBullet(DeltaTime);
	const FVector CurrPos = GetActorLocation();
	DrawDebugLine(GetWorld(), PrevPos, CurrPos, TrailColor, false, 1.f, 0, 1.5f);
	PrevPos = CurrPos;

	lifetime += DeltaTime;
	if (lifetime > 3.f)
		this->Destroy();
}

void ABulletActor::SetBullet(float DeltaTime)
{
	const FVector CurrentPos = GetActorLocation();
	// Default Accel = Gravity
	FVector Accel = FVector(0.f, 0.f, GetWorld()->GetGravityZ());
	const float Speed = Velocity.Size();
	if (Speed > KINDA_SMALL_NUMBER)
		Accel += -Velocity * 0.8f; // Air Drag

	Velocity += Accel * DeltaTime;
	if (Velocity.SizeSquared() < 1.f)
		Velocity = FVector::ZeroVector;
    const FVector NextPos = CurrentPos + Velocity * DeltaTime;

	SetActorLocation(NextPos);
    SetActorRotation(UKismetMathLibrary::MakeRotFromZX(Velocity, GetActorUpVector()));
	
}



