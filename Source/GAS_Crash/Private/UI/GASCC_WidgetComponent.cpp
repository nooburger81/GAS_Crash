// Copyright Sebastian Gaming 2026


#include "UI/GASCC_WidgetComponent.h"
#include "AbilitySystem/GASCC_AbilitySystemComponent.h"
#include "AbilitySystem/GASCC_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/GASCC_CharacterBase.h"
#include "UI/GASCC_AttributeWidget.h"

void UGASCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		CrashCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
	}
	InitializeAttributeDelegate();
	
}

void UGASCC_WidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<AGASCC_CharacterBase>(GetOwner());
	AttributeSet = Cast<UGASCC_AttributeSet>(CrashCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UGASCC_AbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
}

bool UGASCC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AbilitySystemComponent.IsValid();
}

void UGASCC_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UGASCC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGASCC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGASCC_AttributeSet>(AS);

	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
	
}

void UGASCC_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // For checking the owned widget object.

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UGASCC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair)
{
	UGASCC_AttributeWidget* AttributeWidget = Cast<UGASCC_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // We only care about GASCC Attribute Widgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe to matching attributes

	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // Initial values

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // For changes during the game
	});
}
