// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CODMainPlayerCharacter.generated.h"

UCLASS()
class COD_API ACODMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACODMainPlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<class UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Character, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonArmMesh;

	
};
