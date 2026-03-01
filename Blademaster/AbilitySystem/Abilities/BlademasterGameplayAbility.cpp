#include "AbilitySystem/Abilities/BlademasterGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BlademasterAbilitySystemComponent.h"

void UBlademasterGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	if (ActivationPolicy == EBlademasterActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UBlademasterGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                  const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UBlademasterGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ActivationPolicy == EBlademasterActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

EBlademasterActivationPolicy UBlademasterGameplayAbility::GetActivationPolicy() const
{
	return ActivationPolicy;
}

UBlademasterAbilitySystemComponent* UBlademasterGameplayAbility::
GetBlademasterAbilitySystemComponentFromActorInfo() const
{
	return Cast<UBlademasterAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}

bool UBlademasterGameplayAbility::HasMatchingGameplayTag(const FGameplayTag& TagToCheck) const
{
	if (const UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo())
	{
		return AbilitySystem->HasMatchingGameplayTag(TagToCheck);
	}
	
	return false;
}
