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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UCapsuleComponent* Collision;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float BulletSpeed = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDebug = false;
	
private:
	
	FVector Velocity;

	UPROPERTY(EditAnywhere, Category="Debug")
	float TrailLifeTime = 1.0f;

	UPROPERTY(EditAnywhere, Category="Debug")
	FColor TrailColor = FColor::Red;

	FVector PrevPos;
	
	void SetBullet (float DeltaTime);

	float lifetime = 0.f;
};
