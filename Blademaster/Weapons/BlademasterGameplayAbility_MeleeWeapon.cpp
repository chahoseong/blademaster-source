#include "Weapons/BlademasterGameplayAbility_MeleeWeapon.h"
#include "AbilitySystemComponent.h"
#include "BlademasterGameplayTags.h"
#include "Combat/BlademasterComboComponent.h"
#include "Weapons/BlademasterMeleeWeaponInstance.h"

UBlademasterGameplayAbility_MeleeWeapon::UBlademasterGameplayAbility_MeleeWeapon()
{
}

bool UBlademasterGameplayAbility_MeleeWeapon::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	
	const bool bIsAttacking = HasMatchingGameplayTag(BlademasterGameplayTags::State_Attacking);
	if (bIsAttacking && bSupportsCombo)
	{
		if (HasMatchingGameplayTag(BlademasterGameplayTags::State_Combo_Enabled))
		{
			return true;
		}
		
		if (UBlademasterComboComponent* ComboComponent = GetComboComponent())
		{
			const FGameplayTag& InputTag = FindInputTag();
			ComboComponent->PushInput(InputTag);
		}
		
		return false;
	}
	
	return !bIsAttacking;
}

void UBlademasterGameplayAbility_MeleeWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bSupportsCombo)
	{
		UBlademasterComboComponent* ComboComponent = GetComboComponent();
		
	}
}

void UBlademasterGameplayAbility_MeleeWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (bSupportsCombo)
	{
		if (UBlademasterComboComponent* ComboComponent = GetComboComponent())
		{
			ComboComponent->CloseComboWindow();
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBlademasterGameplayAbility_MeleeWeapon::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	if (bSupportsCombo)
	{
		if (HasMatchingGameplayTag(BlademasterGameplayTags::State_Combo_Enabled))
		{
			K2_InputPressed();
		}
		else
		{
			if (UBlademasterComboComponent* ComboComponent = GetComboComponent())
			{
				const FGameplayTag& InputTag = FindInputTag();
				ComboComponent->PushInput(InputTag);
			}
		}
	}
}

const FGameplayTag& UBlademasterGameplayAbility_MeleeWeapon::FindInputTag() const
{
	if (const FGameplayAbilitySpec* AbilitySpec = GetCurrentAbilitySpec())
	{
		for (const FGameplayTag& Tag : AbilitySpec->GetDynamicSpecSourceTags())
		{
			if (Tag.MatchesTag(BlademasterGameplayTags::Input_Action))
			{
				return Tag;
			}
		}
	}
	
	return FGameplayTag::EmptyTag;
}

UBlademasterMeleeWeaponInstance* UBlademasterGameplayAbility_MeleeWeapon::GetWeaponInstance() const
{
	return Cast<UBlademasterMeleeWeaponInstance>(GetAssociatedEquipment());
}

UBlademasterComboComponent* UBlademasterGameplayAbility_MeleeWeapon::GetComboComponent() const
{
	if (const AActor* AvatarActor = GetAvatarActorFromActorInfo())
	{
		return AvatarActor->FindComponentByClass<UBlademasterComboComponent>();
	}
	
	return nullptr;
}
