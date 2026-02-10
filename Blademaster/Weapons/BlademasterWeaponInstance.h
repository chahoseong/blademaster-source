#pragma once

#include "CoreMinimal.h"
#include "Equipment/BlademasterEquipmentInstance.h"
#include "BlademasterWeaponInstance.generated.h"

UCLASS()
class BLADEMASTER_API UBlademasterWeaponInstance : public UBlademasterEquipmentInstance
{
	GENERATED_BODY()
	
public:
	virtual void OnEquipped() override;
	virtual void OnUnequipped() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TSubclassOf<UAnimInstance> WeaponAnimLayer;
};
