#include "AbilitySystem/BlademasterAbilitySystemBlueprintLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "BlademasterAbilitySystemComponent.h"

UBlademasterAbilitySystemComponent* UBlademasterAbilitySystemBlueprintLibrary::GetBlademasterAbilitySystemComponent(AActor* Actor)
{
	return Cast<UBlademasterAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UBlademasterAbilitySystemBlueprintLibrary::SetLooseGameplayTag(AActor* Actor, FGameplayTag GameplayTag, int32 Count)
{
	if (!GameplayTag.IsValid())
	{
		return;
	}

	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		AbilitySystem->SetLooseGameplayTagCount(GameplayTag, FMath::Max(0, Count));
	}
}

bool UBlademasterAbilitySystemBlueprintLibrary::HasMatchingGameplayTag(AActor* Actor, const FGameplayTag& TagToCheck)
{
	if (const UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		return AbilitySystem->HasMatchingGameplayTag(TagToCheck);
	}
	
	return false;
}
