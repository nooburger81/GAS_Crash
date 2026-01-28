// Copyright Sebastian Gaming 2026


#include "Utils/GASCC_BlueprintFunctionLibrary.h"
#include "Characters/GASCC_CharacterBase.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UGASCC_BlueprintFunctionLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	if (Dot < 0.5f)
	{
		// Either Left or Right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}
	return EHitDirection::Front;
}

FName UGASCC_BlueprintFunctionLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Front: return FName("Forward");
	case EHitDirection::Back: return FName("Back");
	default: return FName("None");
	}
}

FClosestActorWithTagResult UGASCC_BlueprintFunctionLibrary::FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor)) continue;
		AGASCC_CharacterBase* BaseCharacter = Cast<AGASCC_CharacterBase>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;

		const float Distance = FVector::Dist(Origin, Actor->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}

	FClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = ClosestDistance;

	return Result;
}
