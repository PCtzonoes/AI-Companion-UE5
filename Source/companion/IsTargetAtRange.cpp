// Fill out your copyright notice in the Description page of Project Settings.


#include "IsTargetAtRange.h"

#include "AIController.h"
#include "AttackInfo.h"
#include "BehaviorTree/BlackboardComponent.h"

void UIsTargetAtRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto const AttackInfo = Cast<UAttackInfo>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackInfoKey.SelectedKeyName)
	);
	auto const Target = Cast<APawn>(
		OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName)
	);

	if (!Target || !AttackInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("No Target or Attack Info found"));
		return;
	}

	auto const Distance = FVector::Dist(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), Target->GetActorLocation());
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Distance <= AttackInfo->Range);
}

void UIsTargetAtRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}
