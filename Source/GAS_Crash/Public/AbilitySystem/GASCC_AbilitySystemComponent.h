// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASCC_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_CRASH_API UGASCC_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;

private:

	void HandleAutoActivatedAbilities(const FGameplayAbilitySpec& AbilitySpec);
};