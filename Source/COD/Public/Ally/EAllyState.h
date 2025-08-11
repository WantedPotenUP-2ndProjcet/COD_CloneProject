// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAllyState : uint8
{
	None UMETA(DisplayName="None"),
	Dead UMETA(DisplayName="Dead"),
	Idle UMETA(DisplayName="Idle"),
	Alert UMETA(DisplayName="Alert"),
	Shoot UMETA(DisplayName="Shoot"),
	Move UMETA(displayName="Move")
};
