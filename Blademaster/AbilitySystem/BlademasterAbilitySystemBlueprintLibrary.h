#pragma once

#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlademasterAbilitySystemBlueprintLibrary.generated.h"

class UBlademasterAbilitySystemComponent;

UCLASS()
class BLADEMASTER_API UBlademasterAbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Blademaster|AbilitySystem")
	static UBlademasterAbilitySystemComponent* GetBlademasterAbilitySystemComponent(AActor* Actor);
	
	UFUNCTION(BlueprintCallable, Category="Blademaster|AbilitySystem")
	static void SetLooseGameplayTag(AActor* Actor, FGameplayTag GameplayTag, int32 Count);
	
	UFUNCTION(BlueprintPure, Category="Blademaster|AbilitySystem")
	static bool HasMatchingGameplayTag(AActor* Actor, const FGameplayTag& TagToCheck);
};
