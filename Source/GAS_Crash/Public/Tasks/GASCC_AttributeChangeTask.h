// Copyright Sebastian Gaming 2026

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GASCC_AttributeChangeTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAtt)

UCLASS()
class GAS_CRASH_API UGASCC_AttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
};
