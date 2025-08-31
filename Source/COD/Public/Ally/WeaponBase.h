// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent * Muzzle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABulletActor> BulletClass;

	UPROPERTY()
	class ABulletActor* Bullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	class UNiagaraSystem* MuzzleVFX = nullptr;

	UFUNCTION(BlueprintCallable, Category="VFX")
	UNiagaraComponent* PlayMuzzleVFX(bool bAttach = true);
	
private:
	
	class AAllyCharacterBase* Owner;
	
	AController* GetOwnerController() const;

	void SpawnBullet();


};





