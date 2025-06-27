#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PFUIKeyIcon.generated.h"

class UProgressBar;
class UImage;

UCLASS()
class PORTFOLIO_API UPFUIKeyIcon : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetToPressKey();
    void SetToHoldKey();
    void SetHoldPercent(const float Percent);

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    
    void UpdateSymbol() const;

protected:
    // Child widgets.
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
    TObjectPtr<UImage> Image_Symbol;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
    TObjectPtr<UProgressBar> PB_Hold;

    // Data.
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Key")
    FKey Key;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Key")
    bool bIsHold;
};
