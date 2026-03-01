#pragma once

#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BlademasterComboComponent.generated.h"

USTRUCT(BlueprintType)
struct FComboContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag AttackType;

	UPROPERTY(BlueprintReadWrite)
	int32 ComboIndex = 0;

	UPROPERTY(BlueprintReadWrite)
	float Timestamp = 0.0f;
};

USTRUCT()
struct FInputBufferEntry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FGameplayTag InputTag;

	UPROPERTY(VisibleAnywhere)
	float Timestamp = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLADEMASTER_API UBlademasterComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlademasterComboComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Blademaster|Combo")
	void OpenComboWindow();
	
	UFUNCTION(BlueprintCallable, Category="Blademaster|Combo")
	void CloseComboWindow();
	
	UFUNCTION(BlueprintCallable, Category="Blademaster|Combo")
	void AdvanceCombo(FGameplayTag AttackType, bool bStartCombo = false);

	UFUNCTION(BlueprintPure, Category="Blademaster|Combo")
	int32 GetNextComboIndex() const;

	UFUNCTION(BlueprintPure, Category="Blademaster|Combo")
	const FComboContext& GetCombo() const;

	UFUNCTION(BlueprintCallable, Category="Blademaster|Combo")
	void ResetCombo();

	UFUNCTION(BlueprintPure, Category="Blademaster|Combo")
	bool IsComboValid() const;
	
	void PushInput(const FGameplayTag& InputTag);
	void ClearInputBuffer();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	FComboContext CurrentCombo;

	UPROPERTY(VisibleAnywhere, Transient)
	TOptional<FInputBufferEntry> BufferedInput;

	UPROPERTY(EditAnywhere, Category="Combat")
	float MaxBufferTime = 0.3f;
	
	UPROPERTY(BlueprintReadOnly, Transient)
	bool bInputBufferClosed = false;
};
