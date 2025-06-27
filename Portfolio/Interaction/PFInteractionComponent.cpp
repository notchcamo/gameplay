#include "PFInteractionComponent.h"

#include "PFInteractableInterface.h"
#include "PFInteractionCommon.h"
#include "PFInteractorComponent.h"

// Constants.
constexpr auto INTERACTION_COLLISION_PROFILE = TEXT("Interaction");

UPFInteractionComponent::UPFInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;

    SetGenerateOverlapEvents(false);
    SetCollisionProfileName(INTERACTION_COLLISION_PROFILE, false);
}

bool UPFInteractionComponent::TryStartInteraction(const UPFInteractorComponent* From)
{
    if (bIsInteractionInProgress)
    {
        return false;
    }
    
    switch (InteractionType)
    {
    case EPFInteractionType::PressKey:
        GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UPFInteractionComponent::FinishInteraction);
        break;

    case EPFInteractionType::HoldKey:
        SetComponentTickEnabled(true);
        CurrentHoldDuration = 0;
        break;
    }

    bIsInteractionInProgress = true;
    Interactor = From;

    return true;
}

void UPFInteractionComponent::FinishInteraction()
{
    check(bIsInteractionInProgress);
    bIsInteractionInProgress = false;

    bool bInteractionSuccess = false;
    
    switch (InteractionType)
    {
    case EPFInteractionType::PressKey:
        bInteractionSuccess = true;
        break;

    case EPFInteractionType::HoldKey:
        SetComponentTickEnabled(false);
        bInteractionSuccess = CurrentHoldDuration >= HoldDuration;
        CurrentHoldDuration = 0.0f;
        break;
    }

    if (bInteractionSuccess)
    {
        if (GetOwner()->Implements<UPFInteractable>() && Interactor.IsValid())
        {
            IPFInteractable::Execute_ReactToInteractionWith(GetOwner(), Interactor->GetOwner());
        }
    }

    Interactor.Reset();
}

void UPFInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentHoldDuration += DeltaTime;
    if (CurrentHoldDuration >= HoldDuration)
    {
        FinishInteraction();
    }
}
