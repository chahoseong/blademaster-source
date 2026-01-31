#include "Characters/BlademasterPlayerCharacter.h"
#include "BlademasterGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BlademasterAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/BlademasterInputComponent.h"
#include "Input/BlademasterInputConfig.h"
#include "Player/BlademasterPlayerState.h"

ABlademasterPlayerCharacter::ABlademasterPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCapsuleComponent()->InitCapsuleSize(25.0f, 88.0f);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(GetRootComponent());
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

void ABlademasterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	AddInputMappings();
	BindInputActions(PlayerInputComponent);
}

void ABlademasterPlayerCharacter::InitializeWithAbilitySystem()
{
	if (const APlayerController* BlademasterPlayerController = GetController<APlayerController>())
	{
		ABlademasterPlayerState* BlademasterPlayerState = 
			BlademasterPlayerController->GetPlayerState<ABlademasterPlayerState>();
		if (BlademasterPlayerState)
		{
			AttributeSet = BlademasterPlayerState->GetBlademasterAttributeSet();
			
			AbilitySystemComponent = BlademasterPlayerState->GetBlademasterAbilitySystemComponent();
			AbilitySystemComponent->InitAbilityActorInfo(BlademasterPlayerState, this);
		}
	}
}

void ABlademasterPlayerCharacter::AddInputMappings() const
{
	if (Controller)
	{
		const APlayerController* PlayerController = GetController<APlayerController>();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			for (const UInputMappingContext* InputMapping : InputConfig->DefaultInputMappings)
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}
}

void ABlademasterPlayerCharacter::BindInputActions(UInputComponent* PlayerInputComponent)
{
	UBlademasterInputComponent* BlademasterInputComponent = Cast<UBlademasterInputComponent>(PlayerInputComponent);
	check(BlademasterInputComponent);
	
	BlademasterInputComponent->BindNativeAction(InputConfig, BlademasterGameplayTags::Input_Action_Move,
		ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
	BlademasterInputComponent->BindNativeAction(InputConfig, BlademasterGameplayTags::Input_Action_Look,
		ETriggerEvent::Triggered, this, &ThisClass::Input_Look, false);
}

void ABlademasterPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementInput = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		
	if (MovementInput.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementInput.Y);
	}
	
	if (MovementInput.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementInput.X);
	}
}

void ABlademasterPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookInput = InputActionValue.Get<FVector2D>();
	
	if (LookInput.X != 0.0f)
	{
		AddControllerYawInput(LookInput.X);
	}
	
	if (LookInput.Y != 0.0f)
	{
		AddControllerPitchInput(LookInput.Y);
	}
}
