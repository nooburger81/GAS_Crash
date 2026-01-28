// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GASCC_GameplayAbility.h"
#include <Navigation/PathFollowingComponent.h>
#include "GASCC_SearchForTarget.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class UAITask_MoveTo;
class AGASCC_CharacterBase;
class UAbilityTask_WaitDelay;
class AGASCC_EnemyCharacter;
class AAIController;
class UGASCC_WaitGameplayEvent;

UCLASS()
class GAS_CRASH_API UGASCC_SearchForTarget : public UGASCC_GameplayAbility
{
	GENERATED_BODY()
public:
	UGASCC_SearchForTarget();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	TWeakObjectPtr<AGASCC_EnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	TWeakObjectPtr<AGASCC_CharacterBase> TargetBaseCharacter;

private:

	UPROPERTY()
	TObjectPtr<UGASCC_WaitGameplayEvent> WaitGameplayEventTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask;

	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> AttackDelayTask;

	void StartSearch();

	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void Search();

	void MoveToTargetAndAttack();

	UFUNCTION()
	void AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);

	UFUNCTION()
	void Attack();
};