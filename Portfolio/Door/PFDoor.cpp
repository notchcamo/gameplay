#include "PFDoor.h"

#include "Interaction/PFInteractionComponent.h"

APFDoor::APFDoor()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;

    // Setup components.

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
    check(RootComponent);

    DoorParent = CreateDefaultSubobject<USceneComponent>(TEXT("DoorParent"));
    check(DoorParent);
    DoorParent->SetupAttachment(RootComponent);

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    check(DoorMesh);
    DoorMesh->SetupAttachment(DoorParent);

    Interaction = CreateDefaultSubobject<UPFInteractionComponent>(TEXT("Interaction"));
    check(Interaction);
    Interaction->SetupAttachment(RootComponent);
}

void APFDoor::BeginPlay()
{
    Super::BeginPlay();

    CloseRotation = DoorParent->GetRelativeRotation();
}

void APFDoor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsRotating)
    {
        ElapsedTime += DeltaSeconds;

        const float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);
        const FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, Alpha);
        
        DoorParent->SetRelativeRotation(NewRotation);

        if (Alpha == 1.0f)
        {
            bIsRotating = false;
        }
    }
}

void APFDoor::StartRotation(const AActor* Interactor)
{
    bIsOpened = !bIsOpened;
    TargetRotation = bIsOpened ? CloseRotation + OpenRotationDelta : CloseRotation;
    
    ElapsedTime = 0.0f;
    InitialRotation = DoorParent->GetRelativeRotation();
    bIsRotating = true;
}

void APFDoor::ReactToInteractionWith_Implementation(AActor* Actor)
{
    StartRotation(Actor);
}
