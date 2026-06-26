#include "Ally/AllyBase_mk2.h"

#include "Ally/AllyAIController.h"
#include "Ally/WeaponBase.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

// ===== Lifecycle =====
AAllyBase_mk2::AAllyBase_mk2()
{
	PrimaryActorTick.bCanEverTick = true;

	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->MaxWalkSpeed = MoveSpeed;
		Move->MaxAcceleration = 2048.f;
		Move->BrakingDecelerationWalking = 2048.f;
		Move->GroundFriction = GroundFriction;
		Move->RotationRate = FRotator(0.f, 720.f, 0.f);
		Move->bOrientRotationToMovement = true;
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAllyAIController::StaticClass();

	AllyID = TEXT("None");

	ConstructorHelpers::FClassFinder<AWeaponBase> WeaponBP(TEXT("/Script/Engine.Blueprint'/Game/Ally/Blueprints/BP_WeaponBase.BP_WeaponBase_C'"));
	if (WeaponBP.Succeeded())
	{
		WeaponClass = WeaponBP.Class;
	}
}

void AAllyBase_mk2::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;

	if (GetMesh())
	{
		GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	}

	SpawnAndAttachWeapon();
	EnterIdle();
}

void AAllyBase_mk2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StateTime += DeltaTime;

	switch (CurrentState)
	{
	case EAllyStateMk2::Idle:
		UpdateIdle(DeltaTime);
		break;
	case EAllyStateMk2::Move:
		UpdateMove(DeltaTime);
		break;
	case EAllyStateMk2::Engage:
		UpdateEngage(DeltaTime);
		break;
	case EAllyStateMk2::Cover:
		UpdateCover(DeltaTime);
		break;
	default:
		break;
	}
}

void AAllyBase_mk2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ===== FSM Public API =====
EAllyStateMk2 AAllyBase_mk2::GetState() const
{
	return CurrentState;
}

// ===== Command API =====
void AAllyBase_mk2::RequestStandby()
{
	bHasMoveRequest = false;
	ClearCombatTarget();
	SetState(EAllyStateMk2::Idle);
}

void AAllyBase_mk2::RequestMove(const FVector& InDestination)
{
	MoveDestination = InDestination;
	bHasMoveRequest = true;
	SetState(EAllyStateMk2::Move);
}

void AAllyBase_mk2::NotifyMoveCompleted()
{
	bHasMoveRequest = false;
	RequestEngageLoop();
}

void AAllyBase_mk2::RequestEngageLoop()
{
	bHasMoveRequest = false;
	SetState(EAllyStateMk2::Engage);
}

// ===== Combat API =====
void AAllyBase_mk2::SetCombatTarget(AActor* InTarget)
{
	TargetActor = InTarget;

	if (CurrentState != EAllyStateMk2::Move && HasValidTarget())
	{
		SetState(EAllyStateMk2::Engage);
	}
}

void AAllyBase_mk2::ClearCombatTarget()
{
	TargetActor = nullptr;

	if (CurrentState == EAllyStateMk2::Engage || CurrentState == EAllyStateMk2::Cover)
	{
		SetState(EAllyStateMk2::Idle);
	}
}

// ===== Weapon API =====
AWeaponBase* AAllyBase_mk2::GetCurWeapon() const
{
	return pCurWeapon;
}

// ===== Weapon Setup =====
void AAllyBase_mk2::SpawnAndAttachWeapon()
{
	if (WeaponClass == nullptr)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}

	pCurWeapon = World->SpawnActor<AWeaponBase>(WeaponClass);
	if (pCurWeapon == nullptr)
	{
		return;
	}

	pCurWeapon->SetOwner(this);

	if (GetMesh())
	{
		pCurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Grip"));
	}
}

// ===== FSM Core =====
void AAllyBase_mk2::SetState(EAllyStateMk2 NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	switch (CurrentState)
	{
	case EAllyStateMk2::Idle:
		ExitIdle();
		break;
	case EAllyStateMk2::Move:
		ExitMove();
		break;
	case EAllyStateMk2::Engage:
		ExitEngage();
		break;
	case EAllyStateMk2::Cover:
		ExitCover();
		break;
	default:
		break;
	}

	CurrentState = NewState;
	StateTime = 0.f;

	switch (CurrentState)
	{
	case EAllyStateMk2::Idle:
		EnterIdle();
		break;
	case EAllyStateMk2::Move:
		EnterMove();
		break;
	case EAllyStateMk2::Engage:
		EnterEngage();
		break;
	case EAllyStateMk2::Cover:
		EnterCover();
		break;
	default:
		break;
	}
}

// ===== FSM Enter =====
void AAllyBase_mk2::EnterIdle()
{
	bAnimMoving = false;
	bAnimEngaging = false;
	bAnimCovered = false;
}

void AAllyBase_mk2::EnterMove()
{
	bAnimMoving = true;
	bAnimEngaging = false;
	bAnimCovered = false;
}

void AAllyBase_mk2::EnterEngage()
{
	bAnimMoving = false;
	bAnimEngaging = true;
	bAnimCovered = false;
	FireTimer = FireInterval;
}

void AAllyBase_mk2::EnterCover()
{
	bAnimMoving = false;
	bAnimEngaging = false;
	bAnimCovered = true;
}

// ===== FSM Exit =====
void AAllyBase_mk2::ExitIdle()
{
}

void AAllyBase_mk2::ExitMove()
{
}

void AAllyBase_mk2::ExitEngage()
{
	FireTimer = 0.f;
}

void AAllyBase_mk2::ExitCover()
{
}

// ===== FSM Update =====
void AAllyBase_mk2::UpdateIdle(float DeltaTime)
{
	if (HasMoveRequest())
	{
		SetState(EAllyStateMk2::Move);
	}
}

void AAllyBase_mk2::UpdateMove(float DeltaTime)
{
	if (HasMoveRequest())
	{
		return;
	}

	SetState(EAllyStateMk2::Idle);
}

void AAllyBase_mk2::UpdateEngage(float DeltaTime)
{
	FireTimer += DeltaTime;
	if (FireTimer >= FireInterval)
	{
		TryFireWeapon();
		FireTimer = 0.f;
	}

	if (StateTime >= EngageDurationBeforeCover)
	{
		SetState(EAllyStateMk2::Cover);
	}
}

void AAllyBase_mk2::UpdateCover(float DeltaTime)
{
	if (StateTime >= CoverDuration)
	{
		SetState(EAllyStateMk2::Engage);
	}
}

// ===== FSM Conditions and Actions =====
bool AAllyBase_mk2::HasValidTarget() const
{
	return IsValid(TargetActor);
}

bool AAllyBase_mk2::HasMoveRequest() const
{
	return bHasMoveRequest;
}

void AAllyBase_mk2::TryFireWeapon()
{
	if (pCurWeapon == nullptr)
	{
		return;
	}

	pCurWeapon->PullTrigger();
	PlayShootMontageIfNeeded();
}

bool AAllyBase_mk2::PlayShootMontageIfNeeded()
{
	if (ShootMontage == nullptr)
	{
		return false;
	}

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent == nullptr)
	{
		return false;
	}

	UAnimInstance* Anim = MeshComponent->GetAnimInstance();
	if (Anim != nullptr && Anim->Montage_IsPlaying(ShootMontage))
	{
		return false;
	}

	const float PlayedLength = PlayAnimMontage(ShootMontage, 1.f);
	return PlayedLength > 0.f;
}
