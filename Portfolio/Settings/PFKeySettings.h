#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PFKeySettings.generated.h"

UCLASS(Config="Key", DefaultConfig)
class PORTFOLIO_API UPFKeySettings final : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    TSoftObjectPtr<UTexture2D> GetSymbol(const FKey Key) const;

protected:
    virtual FName GetCategoryName() const override;
    
private:
    UPROPERTY(Config, EditAnywhere, Category="KeySymbol")
    TMap<FKey, TSoftObjectPtr<UTexture2D>> Symbols;
};
