#pragma once

#include "CoreMinimal.h"
#include "PFInventoryCommon.h"
#include "Components/ActorComponent.h"
#include "PFInventoryComponent.generated.h"


class UPFInventoryItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTFOLIO_API UPFInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPFInventoryComponent();

    void ObtainItem(UPFInventoryItem* Item);
    void RemoveItem(ItemUID UID);

protected:
    UPROPERTY(Transient)
    TArray<UPFInventoryItem*> Items;
};
