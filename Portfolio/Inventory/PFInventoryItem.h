#pragma once

#include "CoreMinimal.h"
#include "PFInventoryCommon.h"
#include "UObject/Object.h"
#include "PFInventoryItem.generated.h"

UCLASS()
class PORTFOLIO_API UPFInventoryItem : public UObject
{
    GENERATED_BODY()

public:
    static UPFInventoryItem* CreateItem(const ItemTID TID, const UWorld* WorldContext);
    
    FORCEINLINE ItemUID GetUID() const { return UID; }
    FORCEINLINE ItemTID GetTID() const { return TID; }

protected:
    ItemUID UID;
    ItemTID TID;
};
