#pragma once

#include "AbilitySystemComponent.h"
#include "BlademasterAbilitySystemComponent.generated.h"

enum class EBlademasterActivationPolicy : uint8;

UCLASS()
class BLADEMASTER_API UBlademasterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();
	
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
	
private:
	void ProcessAbilitiesToActivateWhenInputHeld(TArray<FGameplayAbilitySpecHandle>& OutAbilitiesToActivate);
	void ProcessAbilitiesToActivateWhenInputPressed(TArray<FGameplayAbilitySpecHandle>& OutAbilitiesToActivate);
	void ProcessAbilitiesToActivateWhenInputReleased();

protected:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
