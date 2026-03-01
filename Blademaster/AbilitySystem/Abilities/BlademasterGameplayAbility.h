#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BlademasterGameplayAbility.generated.h"

class UBlademasterAbilitySystemComponent;
class UBlademasterComboComponent;

UENUM(BlueprintType)
enum class EBlademasterActivationPolicy : uint8
{
	OnTriggered,
	WhileInputActive,
	OnGiven,
	Manually,
};

UCLASS()
class BLADEMASTER_API UBlademasterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	EBlademasterActivationPolicy GetActivationPolicy() const;
	
	UFUNCTION(BlueprintPure, Category="Blademaster|AbilitySystem")
	UBlademasterAbilitySystemComponent* GetBlademasterAbilitySystemComponentFromActorInfo() const;
	
protected:
	bool HasMatchingGameplayTag(const FGameplayTag& TagToCheck) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	EBlademasterActivationPolicy ActivationPolicy;
};
