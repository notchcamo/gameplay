#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PFInteractableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UPFInteractable : public UInterface
{
    GENERATED_BODY()
};

class IPFInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    void ReactToInteractionWith(AActor* Actor);
};
