#include "Equipment/BlademasterGameplayAbility_FromEquipment.h"
#include "Equipment/BlademasterEquipmentInstance.h"
#include "Misc/DataValidation.h"

UBlademasterGameplayAbility_FromEquipment::UBlademasterGameplayAbility_FromEquipment(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UBlademasterEquipmentInstance* UBlademasterGameplayAbility_FromEquipment::GetAssociatedEquipment() const
{
	if  (const FGameplayAbilitySpec* AbilitySpec = GetCurrentAbilitySpec())
	{
		return Cast<UBlademasterEquipmentInstance>(AbilitySpec->SourceObject.Get());
	}
	return nullptr;
}

#if WITH_EDITOR
EDataValidationResult UBlademasterGameplayAbility_FromEquipment::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);
	
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	if (InstancingPolicy == EGameplayAbilityInstancingPolicy::NonInstanced)
PRAGMA_ENABLE_DEPRECATION_WARNINGS
	{
		Context.AddError(NSLOCTEXT("Blademaster", "EquipmentAbilityMustBeInstanced", "Equipment ability must be instanced."));
		Result = EDataValidationResult::Invalid;
	}
	
	return Result;
}
#endif
