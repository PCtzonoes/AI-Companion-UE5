// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Combat.generated.h"

class UAttackInfo;
// This class does not need to be modified.
UINTERFACE()
class UCombat : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMPANION_API ICombat
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetTeamID() const = 0;
	virtual void Attack(UAttackInfo* AttackInfo);

	static bool IsFriendly(const TScriptInterface<ICombat>& CombatA, const TScriptInterface<ICombat>& CombatB)
	{
		return CombatA->GetTeamID() == CombatB->GetTeamID();
	}
};
