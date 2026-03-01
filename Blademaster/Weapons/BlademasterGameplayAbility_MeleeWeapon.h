#pragma once

#include "GameplayTagContainer.h"
#include "Equipment/BlademasterGameplayAbility_FromEquipment.h"
#include "BlademasterGameplayAbility_MeleeWeapon.generated.h"

class UBlademasterComboComponent;
class UBlademasterMeleeWeaponInstance;

UCLASS()
class BLADEMASTER_API UBlademasterGameplayAbility_MeleeWeapon : public UBlademasterGameplayAbility_FromEquipment
{
	GENERATED_BODY()
	
public:
	UBlademasterGameplayAbility_MeleeWeapon();
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	UFUNCTION(BlueprintPure, Category = "Blademaster|Ability")
	UBlademasterMeleeWeaponInstance* GetWeaponInstance() const;
	
	UFUNCTION(BlueprintPure, Category="Blademaster|Ability")
	UBlademasterComboComponent* GetComboComponent() const;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void  K2_InputPressed();
	
private:
	const FGameplayTag& FindInputTag() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	FGameplayTag AttackTypeTag;
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	bool bSupportsCombo;
};
