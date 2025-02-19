#include "FriendAI.h"
#include "AttackInfo.h"
#include "companionCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC_AIController.h"

void AFriendAI::BeginPlay()
{
	Super::BeginPlay();
	const auto CompanionCharacter = Cast<AcompanionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!CompanionCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("No Companion Character found"));
		return;
	}
	CompanionCharacter->OnSwitchAttack.AddDynamic(this, &AFriendAI::SwitchAttack);
	auto const Controller = Cast<ANPC_AIController>(GetController());
	if (!Controller)return;
	const auto BlackboardComp = Controller->GetBlackboardComponent();
	BlackboardComp->SetValueAsObject("Player", CompanionCharacter);
	UE_LOG(LogTemp, Display, TEXT("Player Set by %s"), *GetName());
}

void AFriendAI::SwitchAttack()
{
	UE_LOG(LogTemp, Display, TEXT("Switching Attack"));

	auto const Controller = Cast<ANPC_AIController>(GetController());
	if (!Controller)return;


	const auto BlackboardComp = Controller->GetBlackboardComponent();
	if (!BlackboardComp)return;


	const auto CurrentAttack = Cast<UAttackInfo>(BlackboardComp->GetValueAsObject("CurrentAttack"));
	for (auto const Attack : Attacks)
	{
		if (Attack != CurrentAttack)
		{
			BlackboardComp->SetValueAsObject("CurrentAttack", Attack);
			break;
		}
	}
}
