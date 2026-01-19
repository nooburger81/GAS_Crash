// Copyright Sebastian Gaming 2026
// How to set up character movement input actions


#include "GAS_Crash/Public/Player/GASCC_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameplayTags/GASCCTags.h"

void AGASCC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;
	{
		for (UInputMappingContext* Context : InputMappingContexts)
		{
			InputSubsystem->AddMappingContext(Context, 0);
		}

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (!IsValid(EnhancedInputComponent)) return;
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AGASCC_PlayerController::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGASCC_PlayerController::StopJumping);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGASCC_PlayerController::Move);
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGASCC_PlayerController::Look);

			EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &AGASCC_PlayerController::Primary);
			EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &AGASCC_PlayerController::Secondary);
			EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Started, this, &AGASCC_PlayerController::Tertiary);
		}
	}
}

void AGASCC_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;
	GetCharacter()->Jump();
}

void AGASCC_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;
	GetCharacter()->StopJumping();
}

void AGASCC_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetCharacter())) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	//Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AGASCC_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AGASCC_PlayerController::Primary()
{
	ActivateAbility(GASCCTags::GASCCAbilities::Primary);
}

void AGASCC_PlayerController::Secondary()
{
	ActivateAbility(GASCCTags::GASCCAbilities::Secondary);
}

void AGASCC_PlayerController::Tertiary()
{
	ActivateAbility(GASCCTags::GASCCAbilities::Tertiary);
}

void AGASCC_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}
