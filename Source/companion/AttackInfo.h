// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackInfo.generated.h"

/**
 * 
 */
UCLASS()
class COMPANION_API UAttackInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Attack")
	float Damage = 5.0f;
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Attack")
	float Range = 50.0f;
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = "Attack")
	float Cooldown = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;
};
