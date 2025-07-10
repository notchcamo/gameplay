#include "PFCheatManager.h"

#include "Inventory/PFInventoryComponent.h"
#include "Inventory/PFInventoryItem.h"
#include "PlayerController/PFPlayerController.h"

void UPFCheatManager::CreateItem(const uint32 TID)
{
    if (auto* Item = UPFInventoryItem::CreateItem(TID, GetWorld()))
    {
        if (auto* PC = Cast<APFPlayerController>(GetPlayerController()))
        {
            if (UPFInventoryComponent* Inventory = PC->GetInventory())
            {
                Inventory->ObtainItem(Item);
            }
        }
    }
}
