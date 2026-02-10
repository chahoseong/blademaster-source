#include "Equipment/BlademasterEquipmentInstance.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "BlademasterEquipmentDefinition.h"
#include "GameFramework/Character.h"

UBlademasterEquipmentInstance::UBlademasterEquipmentInstance()
{
}

UWorld* UBlademasterEquipmentInstance::GetWorld() const
{
	if (const APawn* OwningPawn = GetPawn())
	{
		return OwningPawn->GetWorld();
	}
	return nullptr;
}

APawn* UBlademasterEquipmentInstance::GetPawn() const
{
	return Cast<APawn>(GetOuter());
}

APawn* UBlademasterEquipmentInstance::GetTypedPawn(TSubclassOf<APawn> PawnType) const
{
	APawn* Result = nullptr;
	
	if (UClass* ActualPawnType = PawnType)
	{
		if (GetOuter()->IsA(ActualPawnType))
		{
			Result = GetPawn();
		}
	}
	
	return Result;
}

void UBlademasterEquipmentInstance::SetInstigator(UObject* NewInstigator)
{
	Instigator = NewInstigator;
}

UObject* UBlademasterEquipmentInstance::GetInstigator() const
{
	return Instigator;
}

void UBlademasterEquipmentInstance::SpawnEquipmentActor(const FBlademasterEquipmentActorToSpawn& ActorToSpawn)
{
	if (APawn* OwningPawn = GetPawn())
	{
		USceneComponent* AttachTarget = OwningPawn->GetRootComponent();
		
		if (const ACharacter* Character = Cast<ACharacter>(OwningPawn))
		{
			AttachTarget = Character->GetMesh();
		}
		
		AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(
			ActorToSpawn.ActorType,
			FTransform::Identity,
			OwningPawn
		);
		NewActor->FinishSpawning(FTransform::Identity, false);
		NewActor->SetActorRelativeTransform(ActorToSpawn.AttachTransform);
		NewActor->AttachToComponent(AttachTarget, FAttachmentTransformRules::KeepRelativeTransform, ActorToSpawn.AttachSocket);
		SpawnedActor = NewActor;
	}
}

void UBlademasterEquipmentInstance::DestroyEquipmentActor()
{
	if (SpawnedActor)
	{
		SpawnedActor->Destroy();
	}
}

AActor* UBlademasterEquipmentInstance::GetSpawnedActor() const
{
	return SpawnedActor;
}

void UBlademasterEquipmentInstance::OnEquipped()
{
	check(EquipmentDefinition);
	
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn()))
	{
		for (const UBlademasterAbilitySet* AbilitySet : EquipmentDefinition->AbilitySetsToGrant)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystem, &GrantedHandles, this);
		}
	}
	
	SpawnEquipmentActor(EquipmentDefinition->ActorToSpawn);
}

void UBlademasterEquipmentInstance::OnUnequipped()
{
	DestroyEquipmentActor();
	
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn()))
	{
		GrantedHandles.TakeFromAbilitySystem(AbilitySystem);
	}
}
