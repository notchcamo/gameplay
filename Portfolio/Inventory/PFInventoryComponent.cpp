#include "PFInventoryComponent.h"

#include "PFInventoryItem.h"

DEFINE_LOG_CATEGORY(LogPFInventory);

UPFInventoryComponent::UPFInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPFInventoryComponent::ObtainItem(UPFInventoryItem* Item)
{
    if (Item)
    {
        Items.AddUnique(Item);

        UE_LOGFMT(LogPFInventory, Log, "Item obtained. UID: {0}, TID: {1}", Item->GetUID(), Item->GetTID());
    }
}

void UPFInventoryComponent::RemoveItem(ItemUID UID)
{
    UPFInventoryItem** FoundItem = Items.FindByPredicate([UID](UPFInventoryItem* Item)
    {
        return Item && Item->GetUID() == UID;
    });

    if (FoundItem)
    {
        const ItemUID ItemUID = (*FoundItem)->GetUID();
        const ItemTID ItemTID = (*FoundItem)->GetTID();
        
        Items.Remove(*FoundItem);
        
        UE_LOGFMT(LogPFInventory, Log, "Item removed. UID: {}, TID: {}", ItemUID, ItemTID);
    }
}
