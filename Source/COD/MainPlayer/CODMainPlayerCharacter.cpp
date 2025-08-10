// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer/CODMainPlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACODMainPlayerCharacter::ACODMainPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	// if (CharacterMeshRef.Object)
	// {
	// 	FirstPersonArmMesh->SetSkeletalMesh(CharacterMeshRef.Object);
	// }
	//
	// FirstPersonArmMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//
	// static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/MainPlayer/Animation/ABP_MainPlayer.ABP_MainPlayer_C"));
	// if (AnimInstanceClassRef.Class)
	// {
	// 	FirstPersonArmMesh->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	// }
}

