#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "BlademasterEquipmentDefinition.generated.h"

class UBlademasterEquipmentInstance;
class UGameplayAbility;
class UGameplayEffect;
class UBlademasterAbilitySet;

USTRUCT(BlueprintType)
struct FBlademasterEquipmentActorToSpawn
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Equipment")
	TSubclassOf<AActor> ActorType;
	
	UPROPERTY(EditAnywhere, Category="Equipment")
	FName AttachSocket;
	
	UPROPERTY(EditAnywhere, Category = "Equipment")
	FTransform AttachTransform;
};

/**
 * 장비 아이템의 정적 데이터를 정의하는 데이터 에셋
 */
UCLASS(BlueprintType, Const)
class BLADEMASTER_API UBlademasterEquipmentDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	TSubclassOf<UBlademasterEquipmentInstance> EquipmentInstanceType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment", meta = (Categories = "Equipment.Type"))
	FGameplayTag EquipmentType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment", meta = (Categories = "Equipment.Slot"))
	FGameplayTag EquipmentSlot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	FBlademasterEquipmentActorToSpawn ActorToSpawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment")
	TArray<TObjectPtr<const UBlademasterAbilitySet>> AbilitySetsToGrant;
};
