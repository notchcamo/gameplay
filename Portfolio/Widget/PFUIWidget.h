#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PFUIWidget.generated.h"

class APFPlayerCharacter;
class APFPlayerController;

UCLASS()
class PORTFOLIO_API UPFUIWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    APFPlayerController* GetPC() const;
    APFPlayerCharacter* GetCharacter() const;
};
