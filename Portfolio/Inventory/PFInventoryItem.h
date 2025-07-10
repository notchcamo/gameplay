#pragma once

#include "CoreMinimal.h"
#include "PFInventoryCommon.h"
#include "Common/PFTemplateId.h"
#include "UObject/Object.h"
#include "PFInventoryItem.generated.h"

UCLASS()
class PORTFOLIO_API UPFInventoryItem : public UObject
{
    GENERATED_BODY()

public:
    static UPFInventoryItem* CreateItem(const FPFTemplateId TID, const UWorld* WorldContext);
    
    FORCEINLINE ItemUID GetUID() const { return UID; }
    FORCEINLINE FPFTemplateId GetTID() const { return TID; }

protected:
    ItemUID UID;

    UPROPERTY(Transient)
    FPFTemplateId TID;
};
