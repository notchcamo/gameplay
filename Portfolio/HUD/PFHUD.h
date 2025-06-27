#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PFHUD.generated.h"

UCLASS()
class PORTFOLIO_API APFHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess))
	TSubclassOf<UUserWidget> HUDWidgetClass;
};
