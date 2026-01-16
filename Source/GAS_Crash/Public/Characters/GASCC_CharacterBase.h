// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GASCC_CharacterBase.generated.h"

UCLASS(Abstract)
class GAS_CRASH_API AGASCC_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AGASCC_CharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
};
