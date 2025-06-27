
#include "PFPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/PFInteractorComponent.h"

APFPlayerCharacter::APFPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	// Setup character movement
	check(GetCharacterMovement());
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Setup camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	check(SpringArm);
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	// Setup interactor
	Interactor = CreateDefaultSubobject<UPFInteractorComponent>(TEXT("Interactor"));
	check(Interactor);
}

void APFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add default input mappings
	if (const auto* PC = GetController<APlayerController>())
	{
		if (auto* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			for (TSoftObjectPtr<UInputMappingContext>& InputMapping : DefaultInputMappings)
			{
				if (!InputMapping.IsNull())
				{
					InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
				}
			}
		}
	}
}

void APFPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input actions
	auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APFPlayerCharacter::OnTriggerLook);
	EnhancedInputComponent->BindAction(GamePadLookAction, ETriggerEvent::Triggered, this, &APFPlayerCharacter::OnTriggerLook);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APFPlayerCharacter::OnTriggerMove);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APFPlayerCharacter::OnPressInteract);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APFPlayerCharacter::OnReleaseInteract);
}

void APFPlayerCharacter::OnTriggerLook(const FInputActionValue& Value)
{
	const FVector2D& Vector = Value.Get<FVector2D>();

	AddControllerYawInput(Vector.X);
	AddControllerPitchInput(Vector.Y);
}

void APFPlayerCharacter::OnTriggerMove(const FInputActionValue& Value)
{
	const FVector2D& MovementVector = Value.Get<FVector2D>();
	const FRotator Yaw(0, GetControlRotation().Yaw, 0);
	const FRotationMatrix YawRotation(Yaw);

	AddMovementInput(YawRotation.GetUnitAxis(EAxis::X), MovementVector.Y);
	AddMovementInput(YawRotation.GetUnitAxis(EAxis::Y), MovementVector.X);
}

void APFPlayerCharacter::OnPressInteract(const FInputActionValue& Value)
{
	check(Interactor);
	Interactor->TryStartInteraction();
}

void APFPlayerCharacter::OnReleaseInteract(const FInputActionValue& Value)
{
	check(Interactor);
	if (Interactor->IsInteractionInProgress())
	{
		Interactor->FinishInteraction();
	}
}
