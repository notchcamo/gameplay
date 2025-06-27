#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/PFInteractableInterface.h"
#include "PFDoor.generated.h"

class UPFInteractionComponent;

/**
 * Door actor.
 * Assumes all doors are closed at the beginning of the game.
 */
UCLASS()
class PORTFOLIO_API APFDoor : public AActor, public IPFInteractable
{
    GENERATED_BODY()

public:
    APFDoor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    void StartRotation(const AActor* Interactor);
    
    // PFInteractable interface override.
    
    virtual void ReactToInteractionWith_Implementation(AActor* Actor) override;

protected:
    /**
     * Component to rotate.
     * Door mesh will be attached to this.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<USceneComponent> DoorParent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UStaticMeshComponent> DoorMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
    TObjectPtr<UPFInteractionComponent> Interaction;

private:
    /**
     * How far does it rotate when it's opened.
     */
    UPROPERTY(EditAnywhere, Category="Door")
    FRotator OpenRotationDelta = FRotator(0, -90, 0);

    /**
     * How long does it take to open this door.
     */
    UPROPERTY(EditAnywhere, Category="Door")
    float Duration = 1.0f;

    /**
     * The rotation at BeginPlay.
     */
    UPROPERTY()
    FRotator CloseRotation;

    UPROPERTY()
    FRotator InitialRotation;

    UPROPERTY()
    FRotator TargetRotation;

    UPROPERTY()
    float ElapsedTime;

    UPROPERTY()
    bool bIsOpened = false;

    UPROPERTY()
    bool bIsRotating = false;
};
