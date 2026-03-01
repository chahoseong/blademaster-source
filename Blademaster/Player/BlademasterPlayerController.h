#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlademasterPlayerController.generated.h"

class ABlademasterPlayerState;
class UBlademasterAbilitySystemComponent;

UCLASS()
class BLADEMASTER_API ABlademasterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	
	UFUNCTION(BlueprintPure, Category="Blademaster|PlayerController")
	ABlademasterPlayerState* GetBlademasterPlayerState() const;
	
	UFUNCTION(BlueprintPure, Category = "Blademaster|PlayerController")
	UBlademasterAbilitySystemComponent* GetBlademasterAbilitySystemComponent() const;
};
