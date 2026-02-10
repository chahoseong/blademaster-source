#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BlademasterGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EBlademasterActivationPolicy : uint8
{
	OnTriggered,
	OnGiven,
	Manually,
};

UCLASS()
class BLADEMASTER_API UBlademasterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	EBlademasterActivationPolicy ActivationPolicy;
};
