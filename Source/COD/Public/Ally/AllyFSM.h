
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AllyFSM.generated.h"


UENUM(BlueprintType)
enum class EAllyState : uint8
{
	Idle UMETA(DisplayName="Idle"),
	Move UMETA(DisplayName="Move"),
	Shoot UMETA(DisplayName="Shoot"),
	Damage UMETA(DisplayName="Damage"),
	Die UMETA(DisplayName="Die")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COD_API UAllyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAllyFSM();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAllyStateChanged, EAllyState, Old, EAllyState, New);

	UPROPERTY(BlueprintAssignable, Category="FSM")
	FOnAllyStateChanged OnStateChanged; */

	void SetState(EAllyState New);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM")
	EAllyState mState = EAllyState::Idle;	// default

	void IdleState(void);
	void MoveState(void);
	void ShootState(void);
	void DamageState(void);
	void DieState(void);
};
