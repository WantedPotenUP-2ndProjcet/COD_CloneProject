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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess="true"))
	int32 MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess="true"))
	int32 HP = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 300.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess="true"))
	float AttackRange = 3000.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta=(AllowPrivateAccess="true"))
	int32 AttackDamage = 10;

	UPROPERTY(VisibleAnywhere)
	float GroundFriction = 8.f;

	UPROPERTY()
	FName AllyID;

	// class EAllyState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM", meta=(AllowPrivateAccess="true"))
	class UAllyFSM* FsmPtr;


public:
	
	// UFUNCTION(BlueprintCallable)
	void StartFire(void);
	
	// UFUNCTION(BlueprintCallable)
	void StopFire(void);
	
	// UFUNCTION(BlueprintCallable)
	void PlayReload(void);
	
	// UFUNCTION(BlueprintCallable)
	void OnArrivedAtPosition(void);

};





