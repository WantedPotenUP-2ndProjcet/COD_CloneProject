#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AllyCharacterBase.generated.h"

UCLASS()
class COD_API AAllyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAllyCharacterBase();

	virtual void Tick(float DeltaTime) override;
	
	// EAllyState GetState(void);
	// void SetState(EAllyState State);


protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 HP = 1;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	FName AllyID;

	// class EAllyState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM", meta=(AllowPrivateAccess="true"))
	class UAllyFSM* FsmPtr;


public:
	
	UPROPERTY(EditAnywhere, Category="Defense")
	AActor* DefensePoint = nullptr; //ATargetPoint

	UPROPERTY(EditAnywhere, Category="Defense", meta=(ClampMin="0"))
	float DefenseAcceptanceRadius = 90.f;

	// UFUNCTION(BlueprintCallable)
	void StartFire(void);
	
	// UFUNCTION(BlueprintCallable)
	void PlayReload(void);
	
	// UFUNCTION(BlueprintCallable)
	void OnArrivedAtPosition(void);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	class AWeaponBase* pCurWeapon;

	AWeaponBase* GetCurWeapon (void) const;
};





