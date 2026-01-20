// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GASCC_PlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class GAS_CRASH_API AGASCC_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	public:
		AGASCC_PlayerState();
		virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	private:

		UPROPERTY(VisibleAnywhere, Category = "Crash|Abilities")
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

		UPROPERTY()
		TObjectPtr<UAttributeSet> AttributeSet;
};
