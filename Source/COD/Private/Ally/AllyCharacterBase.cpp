// Fill out your copyright notice in the Description page of Project Settings.


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
        Move->MaxWalkSpeed = MoveSpeed;
        Move->MaxAcceleration = 2048.f;
        Move->BrakingDecelerationWalking = 2048.f;
        Move->GroundFriction = GroundFriction;
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

}

void AAllyCharacterBase::StartFire(void)
{
	
}

void AAllyCharacterBase::StopFire(void)
{
	
}

void AAllyCharacterBase::PlayReload(void)
{
	
}

void AAllyCharacterBase::OnArrivedAtPosition(void)
{
	
}

void OnArrivedAtPosition(void)
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, TEXT("%s"), *__FUNCTION__);
}

// Called every frame
void AAllyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}