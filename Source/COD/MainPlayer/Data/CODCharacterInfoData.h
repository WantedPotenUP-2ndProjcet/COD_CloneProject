// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CODCharacterInfoData.generated.h"

/**
 * 
 */
// USTRUCT()
// struct FStatus
// {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere)
// 	float MaxWalkSpeed;
//
// 	UPROPERTY(EditAnywhere)
// 	float MaxRunSpeed;
//
// 	UPROPERTY(EditAnywhere)
// 	float WalkAcceleration;
//
// 	UPROPERTY(EditAnywhere)
// 	float RunAcceleration;
//
// 	UPROPERTY(EditAnywhere)
// 	float MaxHp;
// };

UCLASS()
class COD_API UCODCharacterInfoData : public UPrimaryDataAsset
{
	GENERATED_BODY()

};
