// Copyright Sebastian Gaming 2026


#include "AbilitySystem/GASCC_AbilitySystemComponent.h"

#include "GameplayTags/GASCCTags.h"



void UGASCC_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	HandleAutoActivatedAbilities(AbilitySpec);
	
}

void UGASCC_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		HandleAutoActivatedAbilities(AbilitySpec);
	}
}

void UGASCC_AbilitySystemComponent::HandleAutoActivatedAbilities(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;

	for (const FGameplayTag& Tag: AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(GASCCTags::GASCCAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}
