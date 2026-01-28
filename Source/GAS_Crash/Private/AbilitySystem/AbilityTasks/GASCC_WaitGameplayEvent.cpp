// Copyright Sebastian Gaming 2026


#include "AbilitySystem/AbilityTasks/GASCC_WaitGameplayEvent.h"

UGASCC_WaitGameplayEvent* UGASCC_WaitGameplayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor,
	FGameplayTag EventTag, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	UGASCC_WaitGameplayEvent* MyObj = NewObject<UGASCC_WaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

void UGASCC_WaitGameplayEvent::StartActivation()
{
	Activate();
}
