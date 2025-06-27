#include "PFUIWidget.h"

#include "Character/PFPlayerCharacter.h"
#include "PlayerController/PFPlayerController.h"

APFPlayerController* UPFUIWidget::GetPC() const
{
    return GetOwningPlayer<APFPlayerController>();
}

APFPlayerCharacter* UPFUIWidget::GetCharacter() const
{
    return GetOwningPlayerPawn<APFPlayerCharacter>();
}
