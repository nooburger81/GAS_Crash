// Copyright Sebastian Gaming 2026


#include "AbilitySystem/Abilities/Enemy/GASCC_SearchForTarget.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "AbilitySystem/AbilityTasks/GASCC_WaitGameplayEvent.h"
#include "Characters/GASCC_EnemyCharacter.h"
#include "GameplayTags/GASCCTags.h"
#include "Tasks/AITask_MoveTo.h"
#include "Utils/GASCC_BlueprintFunctionLibrary.h"

UGASCC_SearchForTarget::UGASCC_SearchForTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UGASCC_SearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	OwningEnemy = Cast<AGASCC_EnemyCharacter>(GetAvatarActorFromActorInfo());
	check(OwningEnemy.IsValid());
	OwningAIController = Cast<AAIController>(OwningEnemy->GetController());
	check(OwningAIController.IsValid());

	StartSearch();

	WaitGameplayEventTask = UGASCC_WaitGameplayEvent::WaitGameplayEventToActorProxy(GetAvatarActorFromActorInfo(), GASCCTags::Events::Enemy::EndAttack);
	WaitGameplayEventTask->EventReceived.AddDynamic(this, &ThisClass::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivation();
}

void UGASCC_SearchForTarget::StartSearch()
{
	if (bDrawDebugs) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("UGASCC_SearchForTarget::StartSearch")));
	if (!OwningEnemy.IsValid()) return;
	
	const float SearchDelay = FMath::RandRange(OwningEnemy->MinAttackDelay, OwningEnemy->MaxAttackDelay);
	SearchDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, SearchDelay);
	SearchDelayTask->OnFinish.AddDynamic(this, &ThisClass::Search);
	SearchDelayTask->Activate();
}

void UGASCC_SearchForTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	StartSearch();
}

void UGASCC_SearchForTarget::Search()
{
	const FVector SearchOrigin = GetAvatarActorFromActorInfo()->GetActorLocation();
	FClosestActorWithTagResult ClosestActorResult = UGASCC_BlueprintFunctionLibrary::FindClosestActorWithTag(this, SearchOrigin, CrashTags::Player);

	TargetBaseCharacter = Cast<AGASCC_CharacterBase>(ClosestActorResult.Actor);

	if (!TargetBaseCharacter.IsValid())
	{
		StartSearch();
		return;
	}
	if (TargetBaseCharacter->IsAlive())
	{
		MoveToTargetAndAttack();
	}
	else
	{
		StartSearch();
	}
}

void UGASCC_SearchForTarget::MoveToTargetAndAttack()
{
	if (!OwningEnemy.IsValid() || !OwningAIController.IsValid() || !TargetBaseCharacter.IsValid()) return;
	if (!OwningEnemy->IsAlive())
	{
		StartSearch();
		return;
	}

	MoveToLocationOrActorTask = UAITask_MoveTo::AIMoveTo(
		OwningAIController.Get(),
		FVector(),
		TargetBaseCharacter.Get(),
		OwningEnemy->AcceptanceRadius);

	MoveToLocationOrActorTask->OnMoveTaskFinished.AddUObject(this, &ThisClass::AttackTarget);
	MoveToLocationOrActorTask->ConditionalPerformMove();
	
}

void UGASCC_SearchForTarget::AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	if (Result != EPathFollowingResult::Success)
	{
		StartSearch();
		return;
	}
	OwningEnemy->RotateToTarget(TargetBaseCharacter.Get());
	
	AttackDelayTask = UAbilityTask_WaitDelay::WaitDelay(this, OwningEnemy->GetTimelineLength());
	AttackDelayTask->OnFinish.AddDynamic(this, &ThisClass::Attack);
	AttackDelayTask->Activate();
}

void UGASCC_SearchForTarget::Attack()
{
	const FGameplayTag AttackTag = GASCCTags::GASCCAbilities::Enemy::Attack;
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
}