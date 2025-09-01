#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AllyCharacterBase.generated.h"


UENUM(BlueprintType)
enum class EAllyState : uint8
{
	Idle,
	Ready,
	Move,
	Cover,
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

	UFUNCTION(BlueprintCallable)
	void SetState(EAllyState New);

	UFUNCTION(BlueprintCallable)
	EAllyState GetState() const;
	
	void IdleState();
	void ReadyState();
	void MoveState();
	void CoverState();
	void ShootState();
	void DamageState();
	void DieState();

	UPROPERTY(EditAnywhere, Category="Defense")
	AActor* FirstDefensePoint = nullptr;

	UPROPERTY(EditAnywhere, Category="Defense")
	AActor* SecondDefensePoint = nullptr; //ATargetPoint

	UPROPERTY(EditAnywhere, Category="Defense", meta=(ClampMin="0"))
	float DefenseAcceptanceRadius = 90.f;
	
	UPROPERTY()
	class USceneComponent* SpawnPoint;
	
	// UFUNCTION(BlueprintCallable)
	void OnArrivedAtPosition();

	UFUNCTION(BlueprintCallable, Category ="State")
	bool GetStateMoving ();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	class AWeaponBase* pCurWeapon;

	UPROPERTY(EditDefaultsOnly, Category="Anim")
	class UAnimMontage* ShootMontage = nullptr;
	
	AWeaponBase* GetCurWeapon (void) const;

	bool PlayShootMontageIfNeeded();

protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 HP = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 400.f;

	UPROPERTY(VisibleAnywhere)
	float GroundFriction = 8.f;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FName AllyID;

	float FireTime = 0.f;
	int MaxToCover;
	int ToCover = 3;
	float CoverCool = 0.f;

	UPROPERTY(BlueprintReadWrite, Category ="State", meta = (AllowPrivateAccess = "true"))
	bool bMoving = false;

	UPROPERTY(BlueprintReadWrite, Category ="State", meta = (AllowPrivateAccess = "true"))
	bool bReady = false;

	UPROPERTY(BlueprintReadWrite, Category ="State", meta = (AllowPrivateAccess = "true"))
	bool bShooting = false;

	UPROPERTY(BlueprintReadWrite, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bDamaged = false;

	UPROPERTY(BlueprintReadWrite, Category="State", meta = (AllowPrivateAccess = "true"))
	bool bCovered = false;


	int GetRand(void);
};





