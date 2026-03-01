#include "Combat/BlademasterComboComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/BlademasterAbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BlademasterAbilitySystemComponent.h"
#include "BlademasterGameplayTags.h"
#include "Engine/World.h"

UBlademasterComboComponent::UBlademasterComboComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBlademasterComboComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (const UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	// {
	// 	if (!AbilitySystem->HasMatchingGameplayTag(BlademasterGameplayTags::State_Combo_Enabled) && IsComboValid())
	// 	{
	// 		ResetCombo();
	// 	}
	// }

	// Expire stale buffered input
	if (BufferedInput.IsSet() && GetWorld())
	{
		if (GetWorld()->GetTimeSeconds() - BufferedInput.GetValue().Timestamp > MaxBufferTime)
		{
			ClearInputBuffer();
		}
	}
}

void UBlademasterComboComponent::OpenComboWindow()
{
	if (UBlademasterAbilitySystemComponent* AbilitySystem = UBlademasterAbilitySystemBlueprintLibrary::GetBlademasterAbilitySystemComponent(GetOwner()))
	{
		AbilitySystem->SetLooseGameplayTagCount(BlademasterGameplayTags::State_Combo_Enabled, 1);
		
		if (BufferedInput.IsSet())
		{
			const FInputBufferEntry& InputBuffer = BufferedInput.GetValue();
			if (GetWorld()->GetTimeSeconds() - InputBuffer.Timestamp <= MaxBufferTime)
			{
				AbilitySystem->AbilityInputTagPressed(InputBuffer.InputTag);
			}
			
			BufferedInput.Reset();
		}
	}
}

void UBlademasterComboComponent::CloseComboWindow()
{
	if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		AbilitySystem->SetLooseGameplayTagCount(BlademasterGameplayTags::State_Combo_Enabled, 0);
	}
}

void UBlademasterComboComponent::AdvanceCombo(FGameplayTag AttackType, bool bStartCombo)
{
	if (AttackType.MatchesTag(BlademasterGameplayTags::Attack_Type))
	{
		CurrentCombo.AttackType = MoveTemp(AttackType);
		CurrentCombo.ComboIndex = bStartCombo ? 0 : CurrentCombo.ComboIndex + 1;
		CurrentCombo.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	}
}

int32 UBlademasterComboComponent::GetNextComboIndex() const
{
	return CurrentCombo.ComboIndex + 1;
}

bool UBlademasterComboComponent::IsComboValid() const
{
	return CurrentCombo.AttackType.IsValid() && CurrentCombo.ComboIndex >= 0;
}

const FComboContext& UBlademasterComboComponent::GetCombo() const
{
	return CurrentCombo;
}

void UBlademasterComboComponent::ResetCombo()
{
	CurrentCombo = {};
}

void UBlademasterComboComponent::PushInput(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		FInputBufferEntry Entry;
		Entry.InputTag = InputTag;
		Entry.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
		BufferedInput = Entry;
	}

}

void UBlademasterComboComponent::ClearInputBuffer()
{
	BufferedInput.Reset();
}
