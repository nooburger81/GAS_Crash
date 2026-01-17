// Copyright Sebastian Gaming 2026


#include "GAS_Crash/Public/Characters/GASCC_CharacterBase.h"

#include "AbilitySystemComponent.h"


// Sets default values
AGASCC_CharacterBase::AGASCC_CharacterBase()
{
	
	PrimaryActorTick.bCanEverTick = false;

	//Tick and refresh bone transforms even when not rendered - for animation purposes (e.g., gameplay logic, bone updates) on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AGASCC_CharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AGASCC_CharacterBase::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}	
	
}
