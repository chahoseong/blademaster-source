#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"
#include "ActiveGameplayEffectHandle.h"
#include "BlademasterAbilitySet.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;

/**
 * AbilitySet이 부여한 핸들들을 추적하기 위한 구조체
 * 장비 해제 시 이 핸들들을 이용해 어빌리티/이펙트를 제거합니다.
 */
USTRUCT(BlueprintType)
struct FBlademasterAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);

	void TakeFromAbilitySystem(UAbilitySystemComponent* AbilitySystem);

protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;
};

/**
 * AbilitySet에 포함될 어빌리티 데이터
 */
USTRUCT(BlueprintType)
struct FBlademasterAbilitySet_GameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityType;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, meta=(Categories = "Input.Action"))
	FGameplayTag InputTag;
};

/**
 * AbilitySet에 포함될 이펙트 데이터
 */
USTRUCT(BlueprintType)
struct FBlademasterAbilitySet_GameplayEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectType;

	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * 어빌리티와 게임플레이 이펙트 묶음을 정의하는 데이터 에셋
 */
UCLASS(BlueprintType, Const)
class BLADEMASTER_API UBlademasterAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UBlademasterAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** ASC에 어빌리티와 이펙트를 부여하고, 부여된 핸들을 OutGrantedHandles에 저장합니다. */
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FBlademasterAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FBlademasterAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FBlademasterAbilitySet_GameplayEffect> GrantedGameplayEffects;
};
