#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlademasterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ELocomotionDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right
};

UCLASS()
class BLADEMASTER_API UBlademasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	void UpdateLocationData(float DeltaTime);
	void UpdateRotationData();
	void UpdateVelocityData();
	void UpdateAccelerationData();
	
	ELocomotionDirection SelectLocomotionDirectionFromAngle(float Angle, float DeadZone, 
		ELocomotionDirection CurrentDirection, bool bUseCurrentDirection) const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Location Data")
	FVector WorldLocation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Location Data")
	float DisplacementSinceLastUpdate = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Location Data")
	float DisplacementSpeed = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Rotation Data")
	FRotator WorldRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Rotation Data")
	float YawDeltaSinceLastUpdate = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Rotation Data")
	float YawDeltaSpeed = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Velocity Data")
	FVector LocalVelocity2D;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Velocity Data")
	FVector WorldVelocity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Velocity Data")
	float LocalVelocityDirectionAngle = 0.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Velocity Data")
	ELocomotionDirection LocalVelocityDirection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Velocity Data")
	bool bHasVelocity = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Acceleration Data")
	FVector LocalAcceleration2D;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Acceleration Data")
	bool bHasAcceleration = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings")
	float LocomotionDirectionDeadZone = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFirstUpdate = true;
};
