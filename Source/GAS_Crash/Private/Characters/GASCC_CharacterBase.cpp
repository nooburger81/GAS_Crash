// Copyright Sebastian Gaming 2026


#include "GAS_Crash/Public/Characters/GASCC_CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AGASCC_CharacterBase::AGASCC_CharacterBase()
{
	
	PrimaryActorTick.bCanEverTick = false;

	//Tick and refresh bone transforms even when not rendered - for animation purposes (e.g., gameplay logic, bone updates) on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AGASCC_CharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAlive);
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

void AGASCC_CharacterBase::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect is not set."));

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AGASCC_CharacterBase::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f)
	{
		HandleDeath();
	}
}

void AGASCC_CharacterBase::HandleDeath()
{
	bAlive = false;

	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf( TEXT("%s has died."), *GetName()));
	}
}
void AGASCC_CharacterBase::HandleRespawn()
{
	bAlive = true;
}
