#include "Equipment/BlademasterEquipmentManagerComponent.h"
#include "Equipment/BlademasterEquipmentDefinition.h"
#include "Equipment/BlademasterEquipmentInstance.h"

UBlademasterEquipmentManagerComponent::UBlademasterEquipmentManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UBlademasterEquipmentInstance* UBlademasterEquipmentManagerComponent::Equip(
	const UBlademasterEquipmentDefinition* EquipmentDef)
{
	check(EquipmentDef);
	
	UBlademasterEquipmentInstance* NewInstance = 
		NewObject<UBlademasterEquipmentInstance>(GetOwner(), EquipmentDef->EquipmentInstanceType);
	NewInstance->EquipmentDefinition = EquipmentDef;
	NewInstance->OnEquipped();
	
	EquippedEquipment.Add(NewInstance);
	
	return NewInstance;
}

void UBlademasterEquipmentManagerComponent::Unequip(UBlademasterEquipmentInstance* EquipmentToUnequip)
{
	for (auto It = EquippedEquipment.CreateIterator(); It; ++It)
	{
		if (*It == EquipmentToUnequip)
		{
			EquipmentToUnequip->OnUnequipped();
			It.RemoveCurrent();
			break;
		}
	}
}
