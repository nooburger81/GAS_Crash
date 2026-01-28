// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "GASCC_CharacterBase.h"
#include "GASCC_EnemyCharacter.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GAS_CRASH_API AGASCC_EnemyCharacter : public AGASCC_CharacterBase
{
	GENERATED_BODY()

public:

	AGASCC_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float AcceptanceRadius{1000.f};

	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float MinAttackDelay{.1f};

	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float MaxAttackDelay{.5f};

	UFUNCTION(BlueprintImplementableEvent)
	float GetTimelineLength();

protected:
	
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
