#pragma once

#include "EnhancedInputComponent.h"
#include "BlademasterInputConfig.h"
#include "BlademasterInputComponent.generated.h"

UCLASS()
class BLADEMASTER_API UBlademasterInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class UserClass, typename Func>
	void BindNativeAction(const UBlademasterInputConfig* InputConfig, const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent, UserClass* Object, Func&& Callback, bool bLogIfNotFound);
	
	template <class UserClass, typename PressedFunc, typename ReleasedFunc>
	void BindAbilityActions(const UBlademasterInputConfig* InputConfig, UserClass* Object,
		PressedFunc&& OnPressed, ReleasedFunc&& OnReleased, TArray<uint32>& BindHandles);
};

template <class UserClass, typename Func>
void UBlademasterInputComponent::BindNativeAction(const UBlademasterInputConfig* InputConfig,
	const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, Func&& Callback, bool bLogIfNotFound)
{
	check(InputConfig);
	
	if (const UInputAction* InputAction = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(InputAction, TriggerEvent, Object, Forward<Func>(Callback));
	}
}

template <class UserClass, typename PressedFunc, typename ReleasedFunc>
void UBlademasterInputComponent::BindAbilityActions(const UBlademasterInputConfig* InputConfig, UserClass* Object,
	PressedFunc&& OnPressed, ReleasedFunc&& OnReleased, TArray<uint32>& BindHandles)
{
	check(InputConfig);
	
	for (const FBlademasterInputAction& BlademasterInputAction : InputConfig->AbilityInputActions)
	{
		if (BlademasterInputAction.IsValid())
		{
			if (OnPressed)
			{
				uint32 Handle = BindAction(
					BlademasterInputAction.InputAction,
					ETriggerEvent::Triggered,
					Object,
					Forward<PressedFunc>(OnPressed),
					BlademasterInputAction.InputTag
				).GetHandle();
				BindHandles.Add(Handle);
			}
			
			if (OnReleased)
			{
				uint32 Handle = BindAction(
					BlademasterInputAction.InputAction,
					ETriggerEvent::Completed,
					Object,
					Forward<ReleasedFunc>(OnReleased),
					BlademasterInputAction.InputTag
				).GetHandle();
				BindHandles.Add(Handle);
			}
		}
	}
}
