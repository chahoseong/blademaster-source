#include "AbilitySystem/BlademasterAbilitySystemComponent.h"

#include "BlademasterGameplayTags.h"
#include "Abilities/BlademasterGameplayAbility.h"

void UBlademasterAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	if (HasMatchingGameplayTag(BlademasterGameplayTags::Gameplay_AbilityInputBlocked))
	{
		ClearAbilityInput();
		return;
	}
	
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	ProcessAbilitiesToActivateWhenInputHeld(AbilitiesToActivate);
	ProcessAbilitiesToActivateWhenInputPressed(AbilitiesToActivate);
	
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}
	
	ProcessAbilitiesToActivateWhenInputReleased();
	
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UBlademasterAbilitySystemComponent::ProcessAbilitiesToActivateWhenInputHeld(
	TArray<FGameplayAbilitySpecHandle>& OutAbilitiesToActivate)
{
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const UBlademasterGameplayAbility* AbilityDefault = 
					Cast<UBlademasterGameplayAbility>(AbilitySpec->Ability);
				
				if (AbilityDefault && AbilityDefault->GetActivationPolicy() == EBlademasterActivationPolicy::WhileInputActive)
				{
					OutAbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}
}

void UBlademasterAbilitySystemComponent::ProcessAbilitiesToActivateWhenInputPressed(
	TArray<FGameplayAbilitySpecHandle>& OutAbilitiesToActivate)
{
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;
				
				if (AbilitySpec->IsActive())
				{
					// Ability is active so pass along the input event.
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const UBlademasterGameplayAbility* BlademasterAbilityDefault = 
						Cast<UBlademasterGameplayAbility>(AbilitySpec->Ability);
					if (BlademasterAbilityDefault && BlademasterAbilityDefault->GetActivationPolicy() == EBlademasterActivationPolicy::OnTriggered)
					{
						OutAbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}
}

void UBlademasterAbilitySystemComponent::ProcessAbilitiesToActivateWhenInputReleased()
{
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;
				
				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}
}

void UBlademasterAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UBlademasterAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UBlademasterAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void UBlademasterAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	
	if (Spec.IsActive())
	{
		const UGameplayAbility* Instance = Spec.GetPrimaryInstance();
		FPredictionKey OriginalPredictionKey = Instance->GetCurrentActivationInfo().GetActivationPredictionKey();
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, OriginalPredictionKey);
	}
}

void UBlademasterAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);
	
	if (Spec.IsActive())
	{
		const UGameplayAbility* Instance = Spec.GetPrimaryInstance();
		FPredictionKey OriginalPredictionKey = Instance->GetCurrentActivationInfo().GetActivationPredictionKey();
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, OriginalPredictionKey);
	}
}
