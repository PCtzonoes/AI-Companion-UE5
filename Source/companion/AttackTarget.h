// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class COMPANION_API UAttackTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UAttackTarget()
	{
		NodeName = TEXT("Attack Target");
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
