// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsTargetAtRange.generated.h"

/**
 * 
 */
UCLASS()
class COMPANION_API UIsTargetAtRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UIsTargetAtRange()
	{
		NodeName = TEXT("Is Target At Range");
		bNotifyBecomeRelevant = true;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector AttackInfoKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
