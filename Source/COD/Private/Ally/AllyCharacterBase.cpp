
#include "Ally/AllyCharacterBase.h"
#include "Ally/AllyFSM.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ally/AllyAIController.h"

// Sets default values
AAllyCharacterBase::AAllyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FsmPtr = CreateDefaultSubobject<UAllyFSM>(TEXT("FSM"));

	if (auto* Move = GetCharacterMovement())
    {
        Move->MaxWalkSpeed = 300.f;
        Move->MaxAcceleration = 2048.f;
        Move->BrakingDecelerationWalking = 2048.f;
        Move->GroundFriction = 8.f;
        Move->RotationRate = FRotator(0, 720, 0);

        // 자리에서 조준 회전을 컨트롤러로 제어하려면:
        Move->bOrientRotationToMovement = false;
        bUseControllerRotationYaw = true;
    }

    // 에디터배치/스폰 시 자동으로 AI가 점유하도록
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // 이 캐릭터를 기본으로 조종할 AI 컨트롤러 지정
    AIControllerClass = AAllyAIController::StaticClass();

	AllyID = TEXT("None");
}

// Called when the game starts or when spawned
void AAllyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

    /* if(WeaponClass)
    {
        pCurWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
        pCurWeapon->SetOwner(this);
        pCurWeapon->SetupAttachment(GetMesh());
    } */

    if (DefensePoint)
    {
        if (AAllyAIController* AC = Cast<AAllyAIController>(GetController()))
        {
            AC->MoveDefenseLocation(DefensePoint->GetActorLocation(), DefenseAcceptanceRadius);
        }
    }
}

void AAllyCharacterBase::StartFire(void)
{
	FsmPtr->SetState(EAllyState::Shoot);
}

void AAllyCharacterBase::PlayReload(void)
{
	
}

void AAllyCharacterBase::OnArrivedAtPosition(void)
{
	if(GEngine)
	{
		const FString CurFunc = ANSI_TO_TCHAR(__FUNCTION__);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, CurFunc);
	}
    // begin combat
}

AWeaponBase* AAllyCharacterBase::GetCurWeapon(void) const
{
    return pCurWeapon;
}


// Called every frame
void AAllyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}