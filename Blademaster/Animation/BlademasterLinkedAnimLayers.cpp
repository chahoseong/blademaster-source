#include "Animation/BlademasterLinkedAnimLayers.h"
#include "Animation/BlademasterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBlademasterAnimInstance* UBlademasterLinkedAnimLayers::GetOwningAnimInstance() const
{
	if (const ACharacter* Character = Cast<ACharacter>(GetOwningActor()))
	{
		return Cast<UBlademasterAnimInstance>(Character->GetMesh()->GetAnimInstance());
	}
	
	return nullptr;
}

UCharacterMovementComponent* UBlademasterLinkedAnimLayers::GetCharacterMovement() const
{
	if (const APawn* Pawn = TryGetPawnOwner())
	{
		return Cast<UCharacterMovementComponent>(Pawn->GetMovementComponent());
	}
	return nullptr;
}
