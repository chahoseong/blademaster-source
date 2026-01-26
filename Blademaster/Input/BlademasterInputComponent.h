#pragma once

#include "BlademasterInputConfig.h"
#include "EnhancedInputComponent.h"
#include "BlademasterInputComponent.generated.h"

UCLASS()
class BLADEMASTER_API UBlademasterInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class UserClass, typename Func>
	void BindNativeAction(const UBlademasterInputConfig* InputConfig, const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent, UserClass* Object, Func&& Callback, bool bLogIfNotFound);
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
