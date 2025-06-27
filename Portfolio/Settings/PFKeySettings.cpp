#include "PFKeySettings.h"

TSoftObjectPtr<UTexture2D> UPFKeySettings::GetSymbol(const FKey Key) const
{
    TSoftObjectPtr<UTexture2D> Symbol{};

    if (Symbols.Contains(Key))
    {
        Symbol = Symbols[Key];
    }
    
    return Symbol;
}

FName UPFKeySettings::GetCategoryName() const
{
    return TEXT("PF");
}
