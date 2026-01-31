#include "Characters/BlademasterCharacter.h"
#include "AbilitySystem/BlademasterAbilitySystemComponent.h"

ABlademasterCharacter::ABlademasterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ABlademasterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitializeWithAbilitySystem();
}

void ABlademasterCharacter::InitializeWithAbilitySystem()
{
}

UAbilitySystemComponent* ABlademasterCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;	
}

UBlademasterAbilitySystemComponent* ABlademasterCharacter::GetBlademasterAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBlademasterAttributeSet* ABlademasterCharacter::GetBlademasterAttributeSet() const
{
	return AttributeSet;
}
