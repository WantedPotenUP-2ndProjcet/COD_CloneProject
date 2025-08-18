// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class COD_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float MassKg; 
	float V0;
	float GravityScale;
	float FireAngleRad;
	float MaxRange;
	float Damage;
	float DragK;
	FVector Velocity;

	UPROPERTY(EditAnywhere, Category="Debug")
	bool bDebugTrail = true;

	UPROPERTY(EditAnywhere, Category="Debug")
	float TrailLifeTime = 1.0f;

	UPROPERTY(EditAnywhere, Category="Debug")
	FColor TrailColor = FColor::Red;

	FVector PrevPos;
	
private:
	void CalcFireAngle (FVector TargetLocation);
	void SetBullet (float DeltaTime);
	FVector CalcBallistic (FVector& V, float DeltaTime);
};
