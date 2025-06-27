#include "PFUIInteractionHint.h"

#include "Character/PFPlayerCharacter.h"
#include "Components/TextBlock.h"
#include "Interaction/PFInteractionComponent.h"
#include "Interaction/PFInteractorComponent.h"
#include "Widget/Common/PFUIKeyIcon.h"

void UPFUIInteractionHint::NativeConstruct()
{
    Super::NativeConstruct();

    if (IsVisible())
    {
        SetVisibility(ESlateVisibility::Collapsed);
    }

    if (auto* Interactor = GetInteractor())
    {
        Interactor->OnInteractionTargetAdded.AddUObject(this, &ThisClass::OnInteractionTargetAdded);
        Interactor->OnInteractionTargetRemoved.AddUObject(this, &ThisClass::OnInteractionTargetRemoved);
    }
}

void UPFUIInteractionHint::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (IsVisible())
    {
        if (InteractionTarget.IsValid() && InteractionTarget->GetInteractionType() == EPFInteractionType::HoldKey)
        {
            if (UI_KeyIcon)
            {
                UI_KeyIcon->SetHoldPercent(InteractionTarget->GetHoldPercent());
            }
        }
    }
}

UPFInteractorComponent* UPFUIInteractionHint::GetInteractor() const
{
    UPFInteractorComponent* Interactor = nullptr;
    
    if (auto* Character = GetCharacter())
    {
        Interactor = Character->FindComponentByClass<UPFInteractorComponent>();
    }

    return Interactor;
}

void UPFUIInteractionHint::OnInteractionTargetAdded()
{
    if (!IsVisible())
    {
        SetVisibility(ESlateVisibility::HitTestInvisible);
    }

    if (UPFInteractorComponent* Interactor = GetInteractor())
    {
        if (UPFInteractionComponent* Target = Interactor->GetTarget())
        {
            InteractionTarget = Target;
            
            if (Text_Hint)
            {
                // todo Get text from the string table. (Support localization)
                const FText HintText = FText::FromName(Target->GetHintTextId());
                Text_Hint->SetText(HintText);
            }

            if (UI_KeyIcon)
            {
                const EPFInteractionType InteractionType = Target->GetInteractionType();

                if (InteractionType == EPFInteractionType::PressKey)
                {
                    UI_KeyIcon->SetToPressKey();
                }
                else if (InteractionType == EPFInteractionType::HoldKey)
                {
                    UI_KeyIcon->SetToHoldKey();
                    UI_KeyIcon->SetHoldPercent(0.0f);
                }
            }
        }
    }
}

void UPFUIInteractionHint::OnInteractionTargetRemoved()
{
    InteractionTarget.Reset();
    
    if (IsVisible())
    {
        SetVisibility(ESlateVisibility::Collapsed);
    }
}
