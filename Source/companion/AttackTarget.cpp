// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTarget.h"

#include "AIController.h"
#include "AttackInfo.h"
#include "Combat.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const NPC = Cast<ICombat>(OwnerComp.GetAIOwner()->GetPawn());
	auto const Target = Cast<ICombat>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("CurrentTarget"));

	if (!NPC || !Target)
	{
		UE_LOG(LogTemp, Error, TEXT("No ICombat found"));
		return EBTNodeResult::Failed;
	}

	const auto AttackInfo = Cast<UAttackInfo>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("CurrentAttack"));
	NPC->Attack(AttackInfo);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
