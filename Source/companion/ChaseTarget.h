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

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float AcceptanceRadius = 25.0f;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float StartChaseRange = 50.0f;

public:
	UChaseTarget()
	{
		NodeName = TEXT("Chase Target");
		bNotifyTick = true;
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
