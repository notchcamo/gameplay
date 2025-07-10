#include "PFPlayerController.h"

#include "Inventory/PFInventoryComponent.h"

APFPlayerController::APFPlayerController()
{
    Inventory = CreateDefaultSubobject<UPFInventoryComponent>(TEXT("Inventory"));
    check(Inventory);
}
