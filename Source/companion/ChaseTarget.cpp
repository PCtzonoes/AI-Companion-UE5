// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseTarget.h"

#include "AttackInfo.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

EBTNodeResult::Type UChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("No Target found"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UChaseTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto const Controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner());
	auto const Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	float const DistanceToTarget = FVector::Dist(Controller->GetPawn()->GetActorLocation(), Target->GetActorLocation());
	if (DistanceToTarget <= AcceptanceRadius)
	{
		UE_LOG(LogTemp, Display, TEXT("Target is within stop chase range"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
}
