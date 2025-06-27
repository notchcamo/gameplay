#pragma once

#include "CoreMinimal.h"
#include "PFTextData.generated.h"

USTRUCT(BlueprintType)
struct FPFTextData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY()
    FText KOR;

    UPROPERTY()
    FText ENG;
};
