// Copyright Sebastian Gaming 2026


#include "Characters/GASCC_EnemyCharacter.h"
#include "AbilitySystem/GASCC_AbilitySystemComponent.h"
#include "AbilitySystem/GASCC_AttributeSet.h"


AGASCC_EnemyCharacter::AGASCC_EnemyCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UGASCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGASCC_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGASCC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASCC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	if (!HasAuthority()) return;

	GiveStartupAbilities();
	InitializeAttributes();
}
	

