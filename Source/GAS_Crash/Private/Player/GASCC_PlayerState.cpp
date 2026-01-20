// Copyright Sebastian Gaming 2026


#include "Player/GASCC_PlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/GASCC_AbilitySystemComponent.h"
#include "AbilitySystem/GASCC_AttributeSet.h"


AGASCC_PlayerState::AGASCC_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UGASCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	AttributeSet = CreateDefaultSubobject<UGASCC_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGASCC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
