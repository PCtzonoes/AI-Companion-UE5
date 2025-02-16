// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "NonPlayableCharacter.generated.h"

UCLASS()
class COMPANION_API ANonPlayableCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

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
	void Attack();
};
