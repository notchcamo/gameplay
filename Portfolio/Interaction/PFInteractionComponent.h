#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PFInteractionComponent.generated.h"

class UPFInteractorComponent;

UENUM(BlueprintType)
enum class EPFInteractionType : uint8
{
    PressKey,
    HoldKey,
};

/**
 * Component for interaction targets
 */
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class PORTFOLIO_API UPFInteractionComponent : public UBoxComponent
{
    GENERATED_BODY()

public:
    UPFInteractionComponent();

    bool TryStartInteraction(const UPFInteractorComponent* From);
    void FinishInteraction();

    float GetHoldPercent() const { return CurrentHoldDuration / HoldDuration; }

    FORCEINLINE bool IsInteractionInProgress() const noexcept { return bIsInteractionInProgress; }
    FORCEINLINE EPFInteractionType GetInteractionType() const noexcept { return InteractionType; }
    FORCEINLINE float GetHoldDuration() const noexcept { return HoldDuration; }
    FORCEINLINE FName GetHintTextId() const noexcept { return HintTextId; }

protected:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta=(AllowPrivateAccess))
    EPFInteractionType InteractionType = EPFInteractionType::PressKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta=(AllowPrivateAccess, EditCondition="InteractionType == EPFInteractionType::HoldKey"))
    float HoldDuration = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction", meta=(AllowPrivateAccess))
    FName HintTextId;

    UPROPERTY()
    bool bIsInteractionInProgress = false;

    UPROPERTY()
    float CurrentHoldDuration;

    UPROPERTY()
    TWeakObjectPtr<const UPFInteractorComponent> Interactor;
};
