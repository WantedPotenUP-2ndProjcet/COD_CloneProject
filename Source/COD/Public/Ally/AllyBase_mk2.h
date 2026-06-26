#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AllyBase_mk2.generated.h"

// ===== Ally FSM State =====
UENUM(BlueprintType)
enum class EAllyStateMk2 : uint8
{
	Idle,
	Move,
	Engage,
	Cover,
};

UCLASS()
class COD_API AAllyBase_mk2 : public ACharacter
{
	GENERATED_BODY()

public:
	// ===== Lifecycle =====
	AAllyBase_mk2();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ===== FSM Public API =====
	UFUNCTION(BlueprintCallable, Category="State")
	EAllyStateMk2 GetState() const;

	// ===== Command API =====
	UFUNCTION(BlueprintCallable, Category="Command")
	void RequestStandby();

	UFUNCTION(BlueprintCallable, Category="Command")
	void RequestMove(const FVector& InDestination);

	UFUNCTION(BlueprintCallable, Category="Command")
	void NotifyMoveCompleted();

	UFUNCTION(BlueprintCallable, Category="Command")
	void RequestEngageLoop();

	// ===== Combat API =====
	UFUNCTION(BlueprintCallable, Category="Combat")
	void SetCombatTarget(AActor* InTarget);

	UFUNCTION(BlueprintCallable, Category="Combat")
	void ClearCombatTarget();

	// ===== Weapon API =====
	UFUNCTION(BlueprintCallable, Category="Weapon")
	class AWeaponBase* GetCurWeapon() const;

	bool PlayShootMontageIfNeeded();

	// ===== Defense Point Data =====
	UPROPERTY(EditAnywhere, Category="Defense")
	TObjectPtr<AActor> FirstDefensePoint = nullptr;

	UPROPERTY(EditAnywhere, Category="Defense")
	TObjectPtr<AActor> SecondDefensePoint = nullptr;

	UPROPERTY(EditAnywhere, Category="Defense", meta=(ClampMin="0"))
	float DefenseAcceptanceRadius = 90.f;

protected:
	// ===== Weapon Setup =====
	void SpawnAndAttachWeapon();

private:
	// ===== FSM Core =====
	void SetState(EAllyStateMk2 NewState);

	void EnterIdle();
	void EnterMove();
	void EnterEngage();
	void EnterCover();

	void ExitIdle();
	void ExitMove();
	void ExitEngage();
	void ExitCover();

	void UpdateIdle(float DeltaTime);
	void UpdateMove(float DeltaTime);
	void UpdateEngage(float DeltaTime);
	void UpdateCover(float DeltaTime);

	// ===== FSM Conditions and Actions =====
	bool HasValidTarget() const;
	bool HasMoveRequest() const;
	void TryFireWeapon();

private:
	// ===== FSM Data =====
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess="true"))
	EAllyStateMk2 CurrentState = EAllyStateMk2::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta=(AllowPrivateAccess="true"))
	float StateTime = 0.f;

	// ===== Animation State Data =====
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|State", meta=(AllowPrivateAccess="true"))
	bool bAnimMoving = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|State", meta=(AllowPrivateAccess="true"))
	bool bAnimEngaging = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|State", meta=(AllowPrivateAccess="true"))
	bool bAnimCovered = false;

	// ===== Stats Data =====
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats", meta=(AllowPrivateAccess="true"))
	int32 MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats", meta=(AllowPrivateAccess="true"))
	int32 HP = 1;

	// ===== Movement Data =====
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float GroundFriction = 8.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	FVector MoveDestination = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool bHasMoveRequest = false;

	// ===== Identity Data =====
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Identity", meta=(AllowPrivateAccess="true"))
	FName AllyID;

	// ===== Combat Data =====
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AActor> TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	float FireInterval = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	float EngageDurationBeforeCover = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	float CoverDuration = 3.f;

	float FireTimer = 0.f;

	// ===== Weapon Data =====
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	TObjectPtr<class AWeaponBase> pCurWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Anim")
	TObjectPtr<class UAnimMontage> ShootMontage = nullptr;
};
