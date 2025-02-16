// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_AIController.generated.h"

USTRUCT(BlueprintType)
struct FThreatValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threat")
	float ProximityThreat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Threat")
	float DamageThreat;

	float GetTotalThreat() const;

	FThreatValues() = default;
	FThreatValues(float Proximity, float Damage) : ProximityThreat(Proximity), DamageThreat(Damage) {}
};

inline float FThreatValues::GetTotalThreat() const
{
	return 2 * ProximityThreat + DamageThreat;
}

/**
 * 
 */
UCLASS()
class COMPANION_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TMap<APawn*, FThreatValues> ThreatMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* SightConfig;

	FTimerHandle CombatTimerHandle;

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	ANPC_AIController();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnTargetAcquired(APawn* TargetPawn);
	UFUNCTION(BlueprintCallable, Category = "AI")
	void UpdateThreatBasedOnProximity(APawn* OriginPawn);
	UFUNCTION(BlueprintCallable, Category = "AI")
	void UpdateThreatBasedOnDamage(APawn* OriginPawn, const float Damage);
	UFUNCTION(BlueprintCallable, Category = "AI")
	void StartCombat();
	UFUNCTION(BlueprintCallable, Category = "AI")
	void StopCombat();
	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnDeath();

private:
	void PeriodicThreatUpdate();
};
