// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "GASCC_WaitGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_CRASH_API UGASCC_WaitGameplayEvent : public UAbilityAsync_WaitGameplayEvent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Async", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))
	static UGASCC_WaitGameplayEvent* WaitGameplayEventToActorProxy(AActor* TargetActor, UPARAM(meta=(GameplayTagFilter="GameplayEventTagsCategory")) FGameplayTag EventTag, bool OnlyTriggerOnce = false, bool OnlyMatchExact = true);

	void StartActivation();
};
