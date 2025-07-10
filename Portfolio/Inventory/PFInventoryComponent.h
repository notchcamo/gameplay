#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PFInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTFOLIO_API UPFInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPFInventoryComponent();
};
