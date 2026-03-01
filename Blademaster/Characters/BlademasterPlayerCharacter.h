#pragma once

#include "CoreMinimal.h"
#include "BlademasterCharacter.h"
#include "GameplayTagContainer.h"
#include "BlademasterPlayerCharacter.generated.h"

class UBlademasterComboComponent;
class UBlademasterEquipmentDefinition;
class UBlademasterEquipmentManagerComponent;
struct FInputActionValue;
class UBlademasterInputConfig;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BLADEMASTER_API ABlademasterPlayerCharacter : public ABlademasterCharacter
{
	GENERATED_BODY()

public:
	ABlademasterPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void InitializeWithAbilitySystem() override;
	virtual void BeginPlay() override;
	
private:
	void AddInputMappings() const;
	void BindInputActions(UInputComponent* PlayerInputComponent);
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UBlademasterInputConfig> InputConfig;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Equipment")
	TObjectPtr<UBlademasterEquipmentManagerComponent> EquipmentManagerComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TArray<TObjectPtr<const UBlademasterEquipmentDefinition>> StartupEquipments;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UBlademasterComboComponent> ComboComponent;
};
