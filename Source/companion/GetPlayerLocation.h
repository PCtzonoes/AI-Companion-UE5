// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GetPlayerLocation.generated.h"

/**
 * Assumes that it is a single player game and gets the player location
 */
UCLASS()
class COMPANION_API UGetPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UGetPlayerLocation()
	{
		NodeName = TEXT("Get Player Location");
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
