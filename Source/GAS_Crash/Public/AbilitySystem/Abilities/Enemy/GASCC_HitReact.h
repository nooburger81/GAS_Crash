// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GASCC_GameplayAbility.h"
#include "GASCC_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class GAS_CRASH_API UGASCC_HitReact : public UGASCC_GameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "Crash|Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "Crash|Abilities")
	FVector ToInstigator;
};
