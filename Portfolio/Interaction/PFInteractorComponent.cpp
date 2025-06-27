#include "PFInteractorComponent.h"
#include "PFInteractionComponent.h"
#include "PFInteractionCommon.h"

DEFINE_LOG_CATEGORY(LogPFInteraction);

constexpr ECollisionChannel INTERACTION_TRACE_CHANNEL = ECC_GameTraceChannel1; 

// CVars.
static TAutoConsoleVariable<bool> CVarDebugTrace(
    TEXT("PF.Interaction.DebugTrace"),
    false,
    TEXT("Visualize the result of the trace."),
    ECVF_Cheat
);

UPFInteractorComponent::UPFInteractorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = false;
}

bool UPFInteractorComponent::TryStartInteraction() const
{
    if (Target.IsValid() && !Target->IsInteractionInProgress())
    {
        return Target->TryStartInteraction(this);
    }

    return false;
}

void UPFInteractorComponent::FinishInteraction() const
{
    if (Target.IsValid() && Target->IsInteractionInProgress())
    {
        Target->FinishInteraction();
    }
}

bool UPFInteractorComponent::IsInteractionInProgress() const
{
    if (Target.IsValid())
    {
        return Target->IsInteractionInProgress();
    }

    return false;
}

void UPFInteractorComponent::BeginPlay()
{
    Super::BeginPlay();

    // Set timer for the trace
    GetWorld()->GetTimerManager().SetTimer(TraceTimer, this, &UPFInteractorComponent::UpdateTarget, TraceInterval, true);
}

void UPFInteractorComponent::UpdateTarget()
{
    // Do the line trace.
    check(GetOwner());
    const FVector Start = GetOwner()->GetActorLocation() + TraceStartOffset;

    FVector ViewLocation{};
    FRotator ViewRotation{};
    if (auto* OwnerPawn = GetOwner<APawn>())
    {
        if (auto* PC = OwnerPawn->GetController<APlayerController>())
        {
            PC->GetPlayerViewPoint(ViewLocation, ViewRotation);
        }
    }
    
    const FVector End = Start + ViewRotation.Vector() * TraceDistance;
    
    FHitResult HitResult{};
    
    GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, INTERACTION_TRACE_CHANNEL);
    auto* HitInteraction = Cast<UPFInteractionComponent>(HitResult.GetComponent());
    
    if (HitInteraction)
    {
        bool bTargetChanged = false;
        
        if (Target.IsValid())
        {
            if (Target != HitInteraction)
            {
                if (Target->IsInteractionInProgress())
                {
                    Target->FinishInteraction();
                }

                Target = HitInteraction;
                bTargetChanged = true;
            }
        }
        else
        {
            Target = HitInteraction;
            bTargetChanged = true;
        }

        if (bTargetChanged && OnInteractionTargetAdded.IsBound())
        {
            OnInteractionTargetAdded.Broadcast();
        }
            
        UE_LOGFMT(LogPFInteraction, Log, "New interaction target found. ({0})", HitResult.GetActor()->GetActorLabel());
    }
    else
    {
        if (Target.IsValid())
        {
            if (Target->IsInteractionInProgress())
            {
                Target->FinishInteraction();
            }
            
            Target.Reset();

            if (OnInteractionTargetRemoved.IsBound())
            {
                OnInteractionTargetRemoved.Broadcast();
            }
        }
    }
    
    // Debug - Visualize the trace.
    if (CVarDebugTrace.GetValueOnGameThread())
    {
        const FColor Color = HitInteraction ? FColor::Green : FColor::Red;
        
        DrawDebugLine(GetWorld(), Start, End, Color, false, 2);

        if (HitInteraction)
        {
            DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 8, Color, false, 2);
        }
    }
}
