#pragma once

#include "CoreMinimal.h"
#include "PFTemplateId.generated.h"

#define INVALID_TID 0;

USTRUCT(BlueprintType)
struct FPFTemplateId
{
    GENERATED_BODY()
    
    FPFTemplateId() = default;
    FPFTemplateId(const uint32 ID) : TID(ID) {}
    
    bool IsValid() const { return TID != INVALID_TID; }
    FString ToString() const { return FString::FromInt(TID); }
    
private:
    UPROPERTY(Transient)
    uint32 TID = INVALID_TID;
};
