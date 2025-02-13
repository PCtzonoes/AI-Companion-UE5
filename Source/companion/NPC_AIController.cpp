// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"

#include "NonPlayableCharacter.h"


void ANPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (auto const NPC = Cast<ANonPlayableCharacter>(InPawn))
	{
		if (auto const BehaviorTree = NPC->GetBehaviorTree())
		{
			RunBehaviorTree(BehaviorTree);
		}
	}
}
