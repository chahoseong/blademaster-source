#pragma once

#include "Animation/AnimInstance.h"
#include "BlademasterLinkedAnimLayers.generated.h"

class UCharacterMovementComponent;
class UBlademasterAnimInstance;

UCLASS()
class BLADEMASTER_API UBlademasterLinkedAnimLayers : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintPure, Category="Animation", meta=(BlueprintThreadSafe))
	UBlademasterAnimInstance* GetOwningAnimInstance() const;
	
	UFUNCTION(BlueprintPure, Category="Animation")
	UCharacterMovementComponent* GetCharacterMovement() const;
};
