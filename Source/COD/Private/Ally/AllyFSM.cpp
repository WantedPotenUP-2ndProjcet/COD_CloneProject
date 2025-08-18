#include "Ally/AllyFSM.h"
#include "Ally/AllyCharacterBase.h"

UAllyFSM::UAllyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;

	pOwner = Cast<AAllyCharacterBase>(GetOwner());
}


void UAllyFSM::BeginPlay()
{
	Super::BeginPlay();

	
}

void UAllyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	switch (mState)
	{
	case EAllyState::Idle:
		IdleState();
		break;
	
		case EAllyState::Move:
		MoveState();
		break;
	
		case EAllyState::Shoot:
		ShootState();
		break;
	
		case EAllyState::Damage:
		DamageState();
		break;
	
		case EAllyState::Die:
		DieState();
		break;
	}
}

void UAllyFSM::SetState(EAllyState New)
{
	mState = New;
}

void UAllyFSM::IdleState(void)
{
	
}

void UAllyFSM::MoveState(void)
{
	
}

void UAllyFSM::ShootState(void)
{
}

void UAllyFSM::DamageState(void)
{
	
}

void UAllyFSM::DieState(void)
{
	
}

