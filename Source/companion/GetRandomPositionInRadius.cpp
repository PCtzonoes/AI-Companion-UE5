// Fill out your copyright notice in the Description page of Project Settings.


#include "GetRandomPositionInRadius.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UGetRandomPositionInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const NPC = OwnerComp.GetAIOwner()->GetPawn();
	if (!NPC)
	{
		UE_LOG(LogTemp, Error, TEXT("No NPC found"));
		return EBTNodeResult::Failed;
	}

	auto const NavMesh = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("No NavMesh found"));
		return EBTNodeResult::Failed;
	}

	FNavLocation TargetLocation;
	auto const CurrentPosition = NPC->GetActorLocation();
	if (NavMesh->GetRandomPointInNavigableRadius(CurrentPosition, Radius, TargetLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation.Location);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
