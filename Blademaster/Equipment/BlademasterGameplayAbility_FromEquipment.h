#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BlademasterGameplayAbility.h"
#include "BlademasterGameplayAbility_FromEquipment.generated.h"

class UBlademasterEquipmentInstance;

UCLASS()
class BLADEMASTER_API UBlademasterGameplayAbility_FromEquipment : public UBlademasterGameplayAbility
{
	GENERATED_BODY()
	
public:
	UBlademasterGameplayAbility_FromEquipment(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintPure, Category = "Blademaster|Equipment")
	UBlademasterEquipmentInstance* GetAssociatedEquipment() const;
	
#if WITH_EDITOR
	virtual EDataValidationResult  IsDataValid(FDataValidationContext& Context) const override;
#endif
};
