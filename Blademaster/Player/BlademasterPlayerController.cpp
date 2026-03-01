#include "Player/BlademasterPlayerController.h"
#include "Player/BlademasterPlayerState.h"
#include "AbilitySystem/BlademasterAbilitySystemComponent.h"

void ABlademasterPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UBlademasterAbilitySystemComponent* BlademasterAbilitySystem = GetBlademasterAbilitySystemComponent())
	{
		BlademasterAbilitySystem->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

ABlademasterPlayerState* ABlademasterPlayerController::GetBlademasterPlayerState() const
{
	return CastChecked<ABlademasterPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UBlademasterAbilitySystemComponent* ABlademasterPlayerController::GetBlademasterAbilitySystemComponent() const
{
	const ABlademasterPlayerState* BlademasterPlayerState = GetBlademasterPlayerState();
	return BlademasterPlayerState ? BlademasterPlayerState->GetBlademasterAbilitySystemComponent() : nullptr;
}
