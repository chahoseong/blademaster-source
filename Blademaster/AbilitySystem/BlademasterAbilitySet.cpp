#include "AbilitySystem/BlademasterAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

/**
 * FBlademasterAbilitySet_GrantedHandles
 */
void FBlademasterAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FBlademasterAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FBlademasterAbilitySet_GrantedHandles::TakeFromAbilitySystem(UAbilitySystemComponent* AbilitySystem)
{
	if (!AbilitySystem)
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystem->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystem->RemoveActiveGameplayEffect(Handle);
		}
	}

	AbilitySpecHandles.Empty();
	GameplayEffectHandles.Empty();
}

/**
 * UBlademasterAbilitySet
 */
UBlademasterAbilitySet::UBlademasterAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBlademasterAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FBlademasterAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	if (!AbilitySystem)
	{
		return;
	}

	// 어빌리티 부여
	for (const FBlademasterAbilitySet_GameplayAbility& AbilityToGrant : GrantedGameplayAbilities)
	{
		if (!IsValid(AbilityToGrant.AbilityType))
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityToGrant.AbilityType, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;

		if (AbilityToGrant.InputTag.IsValid())
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);
		}

		const FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystem->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}

	// 이펙트 부여
	for (const FBlademasterAbilitySet_GameplayEffect& EffectToGrant : GrantedGameplayEffects)
	{
		if (!IsValid(EffectToGrant.GameplayEffectType))
		{
			continue;
		}
		
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(SourceObject);

		const FGameplayEffectSpecHandle EffectSpec = AbilitySystem->MakeOutgoingSpec(EffectToGrant.GameplayEffectType, EffectToGrant.EffectLevel, EffectContext);
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
		
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(ActiveGameplayEffectHandle);
		}
	}
}
