#include "PFInventoryItem.h"

#include "GameInstance/PFGameInstance.h"

UPFInventoryItem* UPFInventoryItem::CreateItem(const ItemTID TID, const UWorld* WorldContext)
{
    if (!WorldContext)
    {
        return nullptr;
    }
    
    auto* NewItem = NewObject<UPFInventoryItem>();
    check(NewItem);

    NewItem->UID = WorldContext->GetGameInstanceChecked<UPFGameInstance>()->GenerateItemUID();
    NewItem->TID = TID;

    return NewItem;
}
