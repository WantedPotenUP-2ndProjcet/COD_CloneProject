
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
    SetState(EAllyState::Idle);
	HP = MaxHP;
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

    if(WeaponClass)
    {
        pCurWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
        pCurWeapon->SetOwner(this);
        pCurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Grip"));
    }
}

void AAllyCharacterBase::OnArrivedAtPosition(void)
{
	if(GEngine)
	{
		const FString CurFunc = ANSI_TO_TCHAR(__FUNCTION__);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, CurFunc);
	}
    // begin combat
    SetState(EAllyState::Shoot);
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
		IdleState();
		break;
	
		case EAllyState::Move:
		MoveState();
		break;
	
		case EAllyState::Shoot:
    	FireTime += DeltaTime;
    	if (FireTime > 2.0f)
    	{
    		ShootState();
    		FireTime = 0.f;
    	}
		break;
	
		case EAllyState::Damage:
		DamageState();
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

void AAllyCharacterBase::IdleState()
{
    bMoving = false;
}

void AAllyCharacterBase::MoveState()
{
    bMoving = true;
}

void AAllyCharacterBase::ShootState()
{
    bShooting = true;
	if (!ensure(pCurWeapon != nullptr))
		UE_LOG(LogTemp, Error, TEXT("CharBase::pCurWeapon is NULL"));
	pCurWeapon->PullTrigger();
}

void AAllyCharacterBase::DamageState()
{
	
}

void AAllyCharacterBase::DieState()
{
    
}