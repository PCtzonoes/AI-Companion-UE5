// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"

#include "NonPlayableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


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

ANPC_AIController::ANPC_AIController()
{
	ThreatMap = TMap<APawn*, FThreatValues>();
	if (SightConfig == nullptr)
	{
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

		SightConfig->SightRadius = 600.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->SetMaxAge(7.f);
	}

	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	AAIController::GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void ANPC_AIController::OnTargetAcquired(APawn* TargetPawn)
{
	if (TargetPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Target Pawn"));
		return;
	}
	UE_LOG(LogTemp, Verbose, TEXT("%s - target Acquired: %s"), *GetPawn()->GetName(), *TargetPawn->GetName());

	// Initialize threat level with a starting value
	if (!ThreatMap.Contains(TargetPawn))
	{
		ThreatMap.Add(TargetPawn, FThreatValues()); // Starting threat level
	}
}

void ANPC_AIController::UpdateThreatBasedOnProximity(APawn* OriginPawn)
{
	if (ThreatMap.Contains(OriginPawn))
	{
		auto const Distance = FVector::Dist(GetPawn()->GetActorLocation(), OriginPawn->GetActorLocation());
		// loser distance means higher threat
		float const ProximityThreat = FMath::Clamp(1.0f - (Distance - 200.0f) / 800.0f, 0.0f, 1.0f) * 8;
		ThreatMap[OriginPawn].ProximityThreat = ProximityThreat;

		auto const Enemy = Blackboard->GetValueAsObject("CurrentTarget");
		if (Enemy == nullptr)
			Blackboard->SetValueAsObject("CurrentTarget", OriginPawn);
	}
}

void ANPC_AIController::UpdateThreatBasedOnDamage(APawn* OriginPawn, const float Damage)
{
	if (ThreatMap.Contains(OriginPawn))
		ThreatMap[OriginPawn].DamageThreat += Damage;
	else
		ThreatMap.Add(OriginPawn, FThreatValues(0, 2 * Damage));
}

void ANPC_AIController::StartCombat()
{
	GetWorld()->GetTimerManager().SetTimer(CombatTimerHandle, this,
	                                       &ANPC_AIController::PeriodicThreatUpdate, 2.0f, true);
}

void ANPC_AIController::StopCombat()
{
	GetWorld()->GetTimerManager().ClearTimer(CombatTimerHandle);
}

void ANPC_AIController::PeriodicThreatUpdate()
{
	for (const auto& Elem : ThreatMap)
	{
		UpdateThreatBasedOnProximity(Elem.Key);
	}

	// Sort the threat map
	ThreatMap.ValueSort([](const FThreatValues& A, const FThreatValues& B)
	{
		return A.GetTotalThreat() > B.GetTotalThreat();
	});
	if (ThreatMap.Num() > 0)
	{
		auto const Enemy = ThreatMap.CreateConstIterator().Key();
		Blackboard->SetValueAsObject("CurrentTarget", Enemy);
	}
}

void ANPC_AIController::OnDeath()
{
	StopCombat();
	ThreatMap.Empty();
}
