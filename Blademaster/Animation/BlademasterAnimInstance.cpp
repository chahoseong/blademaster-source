#include "Animation/BlademasterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UBlademasterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	UpdateLocationData(DeltaSeconds);
	UpdateRotationData();
	UpdateVelocityData();
	UpdateAccelerationData();
	
	bIsFirstUpdate = false;
}

void UBlademasterAnimInstance::UpdateLocationData(float DeltaTime)
{
	if (const AActor* OwningActor = GetOwningActor())
	{
		if (bIsFirstUpdate)
		{
			DisplacementSinceLastUpdate = 0.0f;
			DisplacementSpeed = 0.0f;
		}
		else
		{
			DisplacementSinceLastUpdate = (OwningActor->GetActorLocation() - WorldLocation).Size2D();
			DisplacementSpeed = UKismetMathLibrary::SafeDivide(DisplacementSinceLastUpdate, DeltaTime);
		}

		WorldLocation = OwningActor->GetActorLocation();
	}
}

void UBlademasterAnimInstance::UpdateRotationData()
{
	if (const AActor* OwningActor = GetOwningActor())
	{
		if (bIsFirstUpdate)
		{
			YawDeltaSinceLastUpdate = 0.0f;
			YawDeltaSpeed = 0.0f;
		}
		else
		{
			YawDeltaSinceLastUpdate = OwningActor->GetActorRotation().Yaw - WorldRotation.Yaw;
			YawDeltaSpeed = UKismetMathLibrary::SafeDivide(YawDeltaSinceLastUpdate, GetDeltaSeconds());
		}

		WorldRotation = OwningActor->GetActorRotation();
	}
}

void UBlademasterAnimInstance::UpdateVelocityData()
{
	const bool bWasMovingLastUpdate = LocalVelocity2D != FVector::ZeroVector;
	
	if (const APawn* Pawn = TryGetPawnOwner())
	{
		WorldVelocity = Pawn->GetVelocity();
		const FVector WorldVelocity2D(WorldVelocity.X, WorldVelocity.Y, 0.0f);
		LocalVelocity2D = WorldRotation.UnrotateVector(WorldVelocity);
		LocalVelocityDirectionAngle = UKismetAnimationLibrary::CalculateDirection(WorldVelocity2D, WorldRotation);
		LocalVelocityDirection = SelectLocomotionDirectionFromAngle(
			LocalVelocityDirectionAngle,
			LocomotionDirectionDeadZone,
			LocalVelocityDirection,
			bWasMovingLastUpdate
		);
		bHasVelocity = !UKismetMathLibrary::NearlyEqual_FloatFloat(LocalVelocity2D.SizeSquared(), 0.0f); 
	}
}

void UBlademasterAnimInstance::UpdateAccelerationData()
{
	if (const APawn* Pawn = TryGetPawnOwner())
	{
		if (const UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(Pawn->GetMovementComponent()))
		{
			const FVector WorldAcceleration = CharacterMovement->GetCurrentAcceleration();
			const FVector WorldAcceleration2D(WorldAcceleration.X, WorldAcceleration.Y, 0.0f);
			LocalAcceleration2D = WorldRotation.UnrotateVector(WorldAcceleration2D);
			bHasAcceleration = !UKismetMathLibrary::NearlyEqual_FloatFloat(LocalAcceleration2D.SizeSquared2D(), 0.0f);
		}
	}
}

ELocomotionDirection UBlademasterAnimInstance::SelectLocomotionDirectionFromAngle(float Angle, float DeadZone,
                                                                                  ELocomotionDirection CurrentDirection, bool bUseCurrentDirection) const
{
	const float AbsAngle = FMath::Abs(Angle);
	float FwdDeadZone = DeadZone;
	float BwdDeadZone = DeadZone;
	
	if (bUseCurrentDirection)
	{
		switch (CurrentDirection)
		{
		case ELocomotionDirection::Forward:
			FwdDeadZone *= 2.0f;
			break;
		case ELocomotionDirection::Backward:
			BwdDeadZone *= 2.0f;
			break;
		}
	}
	
	if (AbsAngle <= 45.0f + FwdDeadZone)
	{
		return ELocomotionDirection::Forward;
	}
	
	if (AbsAngle >= 135.0f - BwdDeadZone)
	{
		return ELocomotionDirection::Backward;
	}
	
	if (Angle > 0.0f)
	{
		return ELocomotionDirection::Right;
	}
	
	return ELocomotionDirection::Left;
}
