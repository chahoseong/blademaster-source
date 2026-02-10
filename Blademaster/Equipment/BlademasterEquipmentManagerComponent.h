#pragma once

#include "Components/ActorComponent.h"
#include "BlademasterEquipmentManagerComponent.generated.h"

class UBlademasterEquipmentInstance;
class UBlademasterEquipmentDefinition;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLADEMASTER_API UBlademasterEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlademasterEquipmentManagerComponent();
	
	UFUNCTION(BlueprintCallable)
	UBlademasterEquipmentInstance* Equip(const UBlademasterEquipmentDefinition* EquipmentDef);
	
	UFUNCTION(BlueprintCallable)
	void Unequip(UBlademasterEquipmentInstance* EquipmentToUnequip);
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<UBlademasterEquipmentInstance>> EquippedEquipment;
};
