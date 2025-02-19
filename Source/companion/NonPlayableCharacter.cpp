// Fill out your copyright notice in the Description page of Project Settings.


#include "NonPlayableCharacter.h"

#include "AttackInfo.h"
#include "NPC_AIController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ANonPlayableCharacter::ANonPlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSource->RegisterForSense(UAISense_Hearing::StaticClass());
	StimuliSource->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void ANonPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANonPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANonPlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ANonPlayableCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	Life -= DamageAmount;
	if (auto const AIController = Cast<ANPC_AIController>(GetController()))
		AIController->UpdateThreatBasedOnDamage(Cast<APawn>(DamageCauser), DamageAmount);
	else UE_LOG(LogTemp, Error, TEXT("No AI Controller found"));

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ANonPlayableCharacter::Attack(UAttackInfo* AttackInfo)
{
	if (AttackInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Attack Info found"));
		return;
	}

	PlayAnimMontage(AttackInfo->AttackMontage);
}
