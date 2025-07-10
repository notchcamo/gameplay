#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Inventory/PFInventoryCommon.h"
#include "PFGameInstance.generated.h"

UCLASS()
class PORTFOLIO_API UPFGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FORCEINLINE ItemUID GenerateItemUID() { return ItemUIDCounter++; }

private:
    ItemUID ItemUIDCounter = 0;
};
