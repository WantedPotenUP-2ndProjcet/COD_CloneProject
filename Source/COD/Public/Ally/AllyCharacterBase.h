#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AllyCharacterBase.generated.h"


UENUM(BlueprintType)
enum class EAllyState : uint8
{
	Idle,
	Move,
	Shoot,
	Damage,
	Die,
};

UCLASS()
class COD_API AAllyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAllyCharacterBase();

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	EAllyState mState;
	void SetState(EAllyState New);
	void IdleState();
	void MoveState();
	void ShootState();
	void DamageState();
	void DieState();

	UPROPERTY(EditAnywhere, Category="Defense")
	AActor* DefensePoint = nullptr; //ATargetPoint

	UPROPERTY(EditAnywhere, Category="Defense", meta=(ClampMin="0"))
	float DefenseAcceptanceRadius = 90.f;
	
	UPROPERTY(EditAnywhere)
	class USceneComponent* SpawnPoint;
	
	// UFUNCTION(BlueprintCallable)
	void OnArrivedAtPosition();

	UFUNCTION(BlueprintCallable, Category ="State")
	bool GetStateMoving ();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABulletActor> BulletClass;

	UPROPERTY(VisibleAnywhere)
	class AWeaponBase* pCurWeapon;

	AWeaponBase* GetCurWeapon (void) const;

protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 HP = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 300.f;

	UPROPERTY(VisibleAnywhere)
	float GroundFriction = 8.f;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FName AllyID;

	float FireTime = 0.f;
	bool bMoving = false;
	bool bShooting = false;

	
};





