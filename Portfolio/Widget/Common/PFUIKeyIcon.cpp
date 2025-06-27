#include "PFUIKeyIcon.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Settings/PFKeySettings.h"

void UPFUIKeyIcon::SetToPressKey()
{
    bIsHold = false;
    
    if (PB_Hold)
    {
        PB_Hold->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UPFUIKeyIcon::SetToHoldKey()
{
    bIsHold = true;
    
    if (PB_Hold)
    {
        PB_Hold->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
    }
}

void UPFUIKeyIcon::SetHoldPercent(const float Percent)
{
    check(bIsHold);
    
    if (PB_Hold)
    {
        PB_Hold->SetPercent(Percent);
    }
}

void UPFUIKeyIcon::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (IsDesignTime())
    {
        if (bIsHold)
        {
            SetToHoldKey();
        }
        else
        {
            SetToPressKey();
        }

        UpdateSymbol();
    }
}

void UPFUIKeyIcon::NativeConstruct()
{
    Super::NativeConstruct();

    if (bIsHold)
    {
        SetToHoldKey();
    }
    else
    {
        SetToPressKey();
    }

    UpdateSymbol();
}

void UPFUIKeyIcon::UpdateSymbol() const
{
    if (Image_Symbol)
    {
        TSoftObjectPtr<UTexture2D> Symbol = GetDefault<UPFKeySettings>()->GetSymbol(Key);
        Image_Symbol->SetBrushFromSoftTexture(Symbol);
    }
}