#pragma once

#include "CoreMinimal.h"
#include "Widget/PFUIWidget.h"
#include "PFUIHUD.generated.h"

class UPFUIInteractionHint;

UCLASS()
class PORTFOLIO_API UPFUIHUD : public UPFUIWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(BindWidget))
    TObjectPtr<UUserWidget> UI_CrossHair;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(BindWidget))
    TObjectPtr<UPFUIInteractionHint> UI_InteractionHint;
};
