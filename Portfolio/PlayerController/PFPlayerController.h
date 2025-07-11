#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PFPlayerController.generated.h"

class UPFInventoryComponent;

UCLASS()
class PORTFOLIO_API APFPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    APFPlayerController();

    UPFInventoryComponent* GetInventory() const { return Inventory; }

protected:
    UPROPERTY(Transient)
    TObjectPtr<UPFInventoryComponent> Inventory;
};
