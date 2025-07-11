#include "PFInventoryItem.h"

#include "GameInstance/PFGameInstance.h"

UPFInventoryItem* UPFInventoryItem::CreateItem(const FPFTemplateId TID, const UWorld* WorldContext)
{
    if (!WorldContext || !TID.IsValid())
    {
        return nullptr;
    }
    
    auto* NewItem = NewObject<UPFInventoryItem>();
    check(NewItem);

    NewItem->UID = WorldContext->GetGameInstanceChecked<UPFGameInstance>()->GenerateItemUID();
    NewItem->TID = TID;

    return NewItem;
}
