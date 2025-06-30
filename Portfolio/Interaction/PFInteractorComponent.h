#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PFInteractorComponent.generated.h"

class UPFInteractionComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTFOLIO_API UPFInteractorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPFInteractorComponent();

    bool TryStartInteraction() const;
    void FinishInteraction() const;

    bool IsInteractionInProgress() const;

    UPFInteractionComponent* GetTarget() const { return Target.Get(); }

protected:
    virtual void BeginPlay() override;

private:
    /**
     * Find an interaction target or remove it.
     * Use sphere trace to find the closest candidate.
     */
    void UpdateTarget();

public:
    // Delegates.
    
    FSimpleMulticastDelegate OnInteractionTargetAdded;
    FSimpleMulticastDelegate OnInteractionTargetRemoved;

private:
    /**
     * Interaction target
     */
    UPROPERTY()
    TWeakObjectPtr<UPFInteractionComponent> Target;

    // Trace option

    UPROPERTY(EditAnywhere, Category="Interaction")
    float TraceInterval = 0.5f;

    UPROPERTY(EditAnywhere, Category="Interaction")
    FVector TraceStartOffset;

    UPROPERTY(EditAnywhere, Category="Interaction")
    float TraceDistance;

    FTimerHandle TraceTimer{};
};
