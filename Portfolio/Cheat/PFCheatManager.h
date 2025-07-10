#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "Inventory/PFInventoryCommon.h"
#include "PFCheatManager.generated.h"

UCLASS()
class PORTFOLIO_API UPFCheatManager : public UCheatManager
{
    GENERATED_BODY()

public:
    UFUNCTION(Exec, Category="Item")
    void CreateItem(const uint32 TID);
};
