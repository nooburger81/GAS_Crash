// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GASCC_GameplayAbility.h"
#include "GASCC_Primary.generated.h"

/**
 * 
 */
UCLASS()
class GAS_CRASH_API UGASCC_Primary : public UGASCC_GameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	TArray<AActor*> HitBoxOverlapTest();

	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& ActorsHit);

private:
	void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	float HitBoxRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	float HitBoxForwardOffset = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	float HitBoxElevationOffset = 20.0f;
};
