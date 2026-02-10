#include "Weapons/BlademasterWeaponInstance.h"
#include "GameFramework/Character.h"

void UBlademasterWeaponInstance::OnEquipped()
{
	Super::OnEquipped();
	
	if (WeaponAnimLayer)
	{
		if (const ACharacter* Character = Cast<ACharacter>(GetPawn()))
		{
			Character->GetMesh()->LinkAnimClassLayers(WeaponAnimLayer);
		}
	}
}

void UBlademasterWeaponInstance::OnUnequipped()
{
	if (WeaponAnimLayer)
	{
		if (const ACharacter* Character = Cast<ACharacter>(GetPawn()))
		{
			Character->GetMesh()->UnlinkAnimClassLayers(WeaponAnimLayer);
		}
	}
	
	Super::OnUnequipped();
}
