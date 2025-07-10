#include "PFInventoryComponent.h"

#include "PFInventoryItem.h"

UPFInventoryComponent::UPFInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPFInventoryComponent::ObtainItem(UPFInventoryItem* Item)
{
    if (Item)
    {
        Items.AddUnique(Item);
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
        Items.Remove(*FoundItem);
    }
}
