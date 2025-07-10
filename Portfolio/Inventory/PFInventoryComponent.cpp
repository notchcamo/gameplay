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

        UE_LOGFMT(LogPFInventory, Log, "Item obtained. UID: {0}, TID: {1}", Item->GetUID(), Item->GetTID().ToString());
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
        const FPFTemplateId ItemTID = (*FoundItem)->GetTID();
        
        Items.Remove(*FoundItem);
        
        UE_LOGFMT(LogPFInventory, Log, "Item removed. UID: {0}, TID: {1}", ItemUID, ItemTID.ToString());
    }
}
