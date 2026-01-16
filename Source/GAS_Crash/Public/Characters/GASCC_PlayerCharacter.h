// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "GASCC_CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GASCC_PlayerCharacter.generated.h"

UCLASS()
class GAS_CRASH_API AGASCC_PlayerCharacter : public AGASCC_CharacterBase
{
	GENERATED_BODY()

public:
		AGASCC_PlayerCharacter();
		virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
		virtual void PossessedBy(AController* NewController) override;
		virtual void OnRep_PlayerState() override;

private:

	UPROPERTY(visibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(visibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

};
