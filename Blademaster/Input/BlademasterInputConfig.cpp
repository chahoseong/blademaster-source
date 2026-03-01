#include "Input/BlademasterInputConfig.h"
#include "BlademasterLogChannels.h"

bool FBlademasterInputAction::IsValid() const
{
	return InputAction && InputTag.IsValid();
}

const UInputAction* UBlademasterInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag,
                                                                         bool bLogNotFound) const
{
	for (const FBlademasterInputAction& Element : NativeInputActions)
	{
		if (Element.InputAction && Element.InputTag == InputTag)
		{
			return Element.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogBlademaster, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."),
			*InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
