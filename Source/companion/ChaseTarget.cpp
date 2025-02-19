// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseTarget.h"

#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

EBTNodeResult::Type UChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("CurrentTarget"));

	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("No Target found"));
		return EBTNodeResult::Failed;
	}

	auto const Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	return EBTNodeResult::Succeeded;
}
