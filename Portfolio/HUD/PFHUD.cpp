#include "HUD/PFHUD.h"

#include "Blueprint/UserWidget.h"

void APFHUD::BeginPlay()
{
    Super::BeginPlay();

    if (auto* Widget = CreateWidget<UUserWidget>(GetOwningPlayerController(), HUDWidgetClass))
    {
        Widget->AddToViewport();
    }
}
