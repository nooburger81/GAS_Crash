// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GASCC_AbilitySystemComponent.h"
#include "AbilitySystem/GASCC_AttributeSet.h"
#include "Characters/GASCC_CharacterBase.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GASCC_WidgetComponent.generated.h"

class AGASCC_CharacterBase;
class UGASCC_AbilitySystemComponent;
class UGASCC_AttributeSet;
class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_CRASH_API UGASCC_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:


	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<AGASCC_CharacterBase> CrashCharacter;
	TWeakObjectPtr<UGASCC_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UGASCC_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject,
	                                  const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair);
};
