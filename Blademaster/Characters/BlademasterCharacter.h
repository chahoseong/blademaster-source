#pragma once

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BlademasterCharacter.generated.h"

class UBlademasterAttributeSet;
class UBlademasterAbilitySystemComponent;

UCLASS()
class BLADEMASTER_API ABlademasterCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABlademasterCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintPure)
	UBlademasterAbilitySystemComponent* GetBlademasterAbilitySystemComponent() const;
	
	UFUNCTION(BlueprintPure)
	UBlademasterAttributeSet* GetBlademasterAttributeSet() const;
	
protected:
	virtual void InitializeWithAbilitySystem();
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlademasterAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlademasterAttributeSet> AttributeSet;
};
