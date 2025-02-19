// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayableCharacter.h"
#include "FriendAI.generated.h"

/**
 * 
 */
UCLASS()
class COMPANION_API AFriendAI : public ANonPlayableCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SwitchAttack();
};
