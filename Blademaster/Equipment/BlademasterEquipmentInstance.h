#pragma once

#include "UObject/Object.h"
#include "AbilitySystem/BlademasterAbilitySet.h"
#include "BlademasterEquipmentInstance.generated.h"

struct FBlademasterEquipmentAbility;
struct FBlademasterEquipmentActorToSpawn;
class UBlademasterEquipmentDefinition;

UCLASS(Abstract, BlueprintType, Blueprintable)
class BLADEMASTER_API UBlademasterEquipmentInstance : public UObject
{
	GENERATED_BODY()
	
	friend class UBlademasterEquipmentManagerComponent;
	
public:
	UBlademasterEquipmentInstance();
	
	virtual UWorld* GetWorld() const override final;
	
	UFUNCTION(BlueprintPure, Category="Equipment")
	APawn* GetPawn() const;
	
	UFUNCTION(BlueprintPure, Category="Equipment", meta=(DeterminesOutputType=PawnType))
	APawn* GetTypedPawn(TSubclassOf<APawn> PawnType) const;
	
	void SetInstigator(UObject* NewInstigator);
	
	UFUNCTION(BlueprintPure, Category="Equipment")
	UObject* GetInstigator() const;
	
	void SpawnEquipmentActor(const FBlademasterEquipmentActorToSpawn& ActorToSpawn);
	void DestroyEquipmentActor();

	UFUNCTION(BlueprintPure, Category="Equipment")
	AActor* GetSpawnedActor() const;

	virtual void OnEquipped();
	virtual void OnUnequipped();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Equipment")
	TObjectPtr<const UBlademasterEquipmentDefinition> EquipmentDefinition;
	
	UPROPERTY(VisibleAnywhere, Category="Equipment")
	TObjectPtr<UObject> Instigator;
	
	UPROPERTY(VisibleAnywhere, Category="Equipment")
	TObjectPtr<AActor> SpawnedActor;
	
	UPROPERTY()
	FBlademasterAbilitySet_GrantedHandles GrantedHandles;
};
