
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PFPlayerCharacter.generated.h"

class UPFInteractorComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

/**
 * Player's character
 */
UCLASS()
class PORTFOLIO_API APFPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APFPlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	// Look input handler
	void OnTriggerLook(const FInputActionValue& Value);

	// Move input handler
	void OnTriggerMove(const FInputActionValue& Value);

	// Interact input handler
	void OnPressInteract(const FInputActionValue& Value);
	void OnReleaseInteract(const FInputActionValue& Value);

private:
	// Components

	/**
	 * Spring arm for a player camera
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess))
	TObjectPtr<UPFInteractorComponent> Interactor;
	
	// Input Actions
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	TObjectPtr<UInputAction> MouseLookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	TObjectPtr<UInputAction> GamePadLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	TObjectPtr<UInputAction> InteractAction;

	// Input Mapping Contexts

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	TArray<TSoftObjectPtr<UInputMappingContext>> DefaultInputMappings;
};
