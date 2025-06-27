#pragma once

#include "CoreMinimal.h"
#include "Widget/PFUIWidget.h"
#include "PFUIInteractionHint.generated.h"

class UPFInteractionComponent;
class UPFUIKeyIcon;
class UTextBlock;
class UPFInteractorComponent;

UCLASS()
class PORTFOLIO_API UPFUIInteractionHint : public UPFUIWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    UPFInteractorComponent* GetInteractor() const;

    void OnInteractionTargetAdded();
    void OnInteractionTargetRemoved();
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(BindWidget))
    TObjectPtr<UTextBlock> Text_Hint;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(BindWidget))
    TObjectPtr<UPFUIKeyIcon> UI_KeyIcon;

    UPROPERTY()
    TWeakObjectPtr<UPFInteractionComponent> InteractionTarget;
};
