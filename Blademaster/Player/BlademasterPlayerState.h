#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlademasterPlayerState.generated.h"

class UBlademasterAttributeSet;
class UBlademasterAbilitySystemComponent;

UCLASS()
class BLADEMASTER_API ABlademasterPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ABlademasterPlayerState();
	
	UFUNCTION(BlueprintPure)
	UBlademasterAbilitySystemComponent* GetBlademasterAbilitySystemComponent() const;
	
	UFUNCTION(BlueprintPure)
	UBlademasterAttributeSet* GetBlademasterAttributeSet() const;
	
protected:
	UPROPERTY(VisibleAnywhere, Category="AbilitySystem")
	TObjectPtr<UBlademasterAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, Category="AbilitySystem")
	TObjectPtr<UBlademasterAttributeSet> AttributeSet;
};
