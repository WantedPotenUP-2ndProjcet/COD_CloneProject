// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class COD_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	void PullTrigger(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;		// root comp

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;	// mesh -> root 부착

private:
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;
	
	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

	AController* GetOwnerController() const;

};





