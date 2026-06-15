#include "CookingSimulator/Characters/CSCharacter.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACSCharacter::ACSCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
}

void ACSCharacter::Movement(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(FVector(MovementVector.X, MovementVector.Y, 0), 1);
}

void ACSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
    	EnhancedInput->BindAction(MovementInputAction, ETriggerEvent::Triggered,this,&ACSCharacter::Movement);
    }
}
