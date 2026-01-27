// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AbilitySystem/Abilities/GASCC_GameplayAbility.h"
#include "Characters/GASCC_EnemyCharacter.h"
#include "GASCC_SearchForTarget.generated.h"


UCLASS()
class GAS_CRASH_API UGASCC_SearchForTarget : public UGASCC_GameplayAbility
{
	GENERATED_BODY()

public:

	UGASCC_SearchForTarget();
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	TWeakObjectPtr<AGASCC_EnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	
};
