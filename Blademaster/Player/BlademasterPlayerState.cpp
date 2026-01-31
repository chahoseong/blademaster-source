#include "Player/BlademasterPlayerState.h"
#include "AbilitySystem/BlademasterAbilitySystemComponent.h"
#include "AbilitySystem/BlademasterAttributeSet.h"

ABlademasterPlayerState::ABlademasterPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBlademasterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UBlademasterAttributeSet>(TEXT("AttributeSet"));
}

UBlademasterAbilitySystemComponent* ABlademasterPlayerState::GetBlademasterAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBlademasterAttributeSet* ABlademasterPlayerState::GetBlademasterAttributeSet() const
{
	return AttributeSet;
}
