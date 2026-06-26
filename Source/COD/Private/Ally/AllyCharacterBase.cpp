
#include "Ally/AllyCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ally/AllyAIController.h"
#include "Ally/WeaponBase.h"

// Sets default values
AAllyCharacterBase::AAllyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;;

	if (auto* Move = GetCharacterMovement())
    {
        Move->MaxWalkSpeed = MoveSpeed;
        Move->MaxAcceleration = 2048.f;
        Move->BrakingDecelerationWalking = 2048.f;
        Move->GroundFriction = GroundFriction;
        Move->RotationRate = FRotator(0, 720, 0);
        Move->bOrientRotationToMovement = true;

        // 자리에서 조준 회전을 컨트롤러로 제어하려면:
        // bUseControllerRotationYaw = true;
    }

    // 에디터배치/스폰 시 자동으로 AI가 점유하도록
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // 이 캐릭터를 기본으로 조종할 AI 컨트롤러 지정
    AIControllerClass = AAllyAIController::StaticClass();

	AllyID = TEXT("None");
    mState = EAllyState::Idle;

	ConstructorHelpers::FClassFinder<AWeaponBase> tmpBPWeapon(TEXT("/Script/Engine.Blueprint'/Game/Ally/Blueprints/BP_WeaponBase.BP_WeaponBase_C'"));
	if (tmpBPWeapon.Succeeded())
		WeaponClass = tmpBPWeapon.Class;
}

// Called when the game starts or when spawned
void AAllyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
    SetState(EAllyState::Ready);
	HP = MaxHP;
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

    if(WeaponClass)
    {
        pCurWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
        pCurWeapon->SetOwner(this);
        pCurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Grip"));
    }
}

int AAllyCharacterBase::GetRand()
{
	return FMath::RandRange(1, 5);
}

void AAllyCharacterBase::OnArrivedAtPosition(void)
{
    // begin combat
    SetState(EAllyState::Ready);
	bMoving = false;
}

bool AAllyCharacterBase::GetStateMoving(void)
{
    return bMoving;
}

AWeaponBase* AAllyCharacterBase::GetCurWeapon(void) const
{
    return pCurWeapon;
}

// Called every frame
void AAllyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
    switch (mState)
	{
	case EAllyState::Idle:
    	bReady = false;
		IdleState();
		break;

    case EAllyState::Ready:
    	ReadyState();
    	break;
	
	case EAllyState::Move:
		MoveState();
		break;

    case EAllyState::Cover:
    	CoverState();
    	break;
    	
	case EAllyState::Shoot:
    	bMoving = false;
    	bShooting = true;
    	FireTime += DeltaTime;
    	
    	if (FireTime > 2.0f)
    	{ 
    		ShootState();
    		FireTime = 0.f;
    		++ToCover;
    	}
    	if (ToCover > MaxToCover)
    	{
    		SetState(EAllyState::Cover);
    		ToCover = 0;
    	}
		break;
	
	case EAllyState::Die:
		DieState();
		break;
	}

}

void AAllyCharacterBase::SetState(EAllyState New)
{
    this->mState = New;
}

EAllyState AAllyCharacterBase::GetState() const
{
	return this->mState;
}

void AAllyCharacterBase::IdleState()
{
	
}

void AAllyCharacterBase::ReadyState()
{
	bReady = true;
	// if enemy alive
	SetState(EAllyState::Shoot);
}

void AAllyCharacterBase::MoveState()
{
    bMoving = true;
}

void AAllyCharacterBase::ShootState()
{
	//if (!ensure(pCurWeapon != nullptr))
		//UE_LOG(LogTemp, Error, TEXT("CharBase::pCurWeapon is NULL"));
	
	pCurWeapon->PullTrigger();
	PlayAnimMontage(ShootMontage, 1.f);
	// PlayShootMontageIfNeeded();
}

void AAllyCharacterBase::CoverState()
{
	bCovered = true;
	bMoving = false;
	CoverCool+=GetWorld()->GetDeltaSeconds();
	if (CoverCool > 3)
	{
		MaxToCover = GetRand();
		SetState(EAllyState::Shoot);
		CoverCool = 0.f;
	}
}

void AAllyCharacterBase::DieState()
{
	bDamaged = true;
    bMoving = false;
	bShooting = false;
	bReady = false;
	bCovered = false;
}

bool AAllyCharacterBase::PlayShootMontageIfNeeded()
{
	if (!ShootMontage) return false;

	// ACharacter::PlayAnimMontage 사용 권장 (복제/루트모션 처리)
	// 이미 재생 중이면 겹치지 않도록 체크
	if (UAnimInstance* Anim = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr)
	{
		if (Anim->Montage_IsPlaying(ShootMontage))
		{
			return false; // 이미 재생중
		}
	}

	const float PlayedLen = PlayAnimMontage(ShootMontage, 1.f);
	return PlayedLen > 0.f;
}