// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ChaseTarget.generated.h"

/**
 * 
 */
UCLASS()
class COMPANION_API UChaseTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UChaseTarget()
	{
		NodeName = TEXT("Chase Target");
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
