// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "NonPlayableCharacter.generated.h"

class UAttackInfo;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class COMPANION_API ANonPlayableCharacter : public ACharacter, public ICombat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* StimuliSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	int32 TeamID = 1;

	UPROPERTY(EditDefaultsOnly, Category = Combat, meta = (AllowPrivate = "true"))
	float Life = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = Combat, meta = (AllowPrivate = "true"))
	TArray<UAttackInfo*> Attacks;

public:
	// Sets default values for this character's properties
	ANonPlayableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetShortestAttackRange() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual int32 GetTeamID() const override { return TeamID; }

	UFUNCTION(Blueprintable, Category = "Combat")
	virtual void Attack(UAttackInfo* AttackInfo) override;
};
