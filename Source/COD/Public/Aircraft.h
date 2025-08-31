// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Aircraft.generated.h"

UCLASS()
class COD_API AAircraft : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAircraft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="lerp")
	AActor* Target1 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="lerp")
	AActor* Target2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="lerp")
	AActor* Target3 = nullptr;
	
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InitLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* sound;

public:
	UFUNCTION(BlueprintCallable)
	void AirStrike ();
};
