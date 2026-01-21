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

protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
