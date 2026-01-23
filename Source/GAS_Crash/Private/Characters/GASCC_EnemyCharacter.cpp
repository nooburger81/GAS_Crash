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

UAttributeSet* AGASCC_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AGASCC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (!HasAuthority()) return;

	GiveStartupAbilities();
	InitializeAttributes();

	UGASCC_AttributeSet* GASCC_AttributeSet = Cast<UGASCC_AttributeSet>(GetAttributeSet());
	if (!IsValid(GASCC_AttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GASCC_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}	

