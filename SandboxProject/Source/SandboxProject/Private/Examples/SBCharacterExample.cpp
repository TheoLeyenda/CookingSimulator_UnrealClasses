#include "Examples/SBCharacterExample.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SBInteractableInterfaceExample.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASBCharacterExample::ASBCharacterExample()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Configurar tamaño por defecto de la cápsula de colisión nativa
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 2. Modificar parámetros del componente de movimiento nativo sin necesidad de crearlo
	GetCharacterMovement()->JumpZVelocity = 600.f;       // Fuerza del salto
	GetCharacterMovement()->GravityScale = 1.5f;         // Gravedad personalizada
	GetCharacterMovement()->MaxWalkSpeed = 600.f;        // Velocidad máxima al correr
	GetCharacterMovement()->bCanWalkOffLedges = true;    // Puede caerse de bordes
}

void ASBCharacterExample::BeginPlay()
{
	Super::BeginPlay();

	// Añadimos el contexto de mapeo (Input Mapping Context) al subsystem de este jugador local
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASBCharacterExample::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Casteamos el componente de input al nuevo EnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Vinculamos el salto directamente a las funciones nativas heredadas del Character
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Vinculamos el movimiento a nuestra función personalizada
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASBCharacterExample::Move);
	}
}

void ASBCharacterExample::Move(const FInputActionValue& Value)
{
	// Extraemos el vector 2D (Ejes X e Y del joystick o WASD)
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Encontramos hacia dónde mira la cámara/controlador (ignorando la inclinación vertical)
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Calculamos la dirección hacia adelante y la dirección hacia la derecha respecto al mundo
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Añadimos el movimiento al CharacterMovementComponent nativo
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

AActor* ASBCharacterExample::GetActorInFrontOfPlayer()
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;
	
	FVector TraceStart;
	FRotator PlayerRotation;
	GetActorEyesViewPoint(TraceStart, PlayerRotation);

	FVector ForwardVector = PlayerRotation.Vector();
	FVector TraceEnd = TraceStart + (ForwardVector * InteractionDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility, 
		QueryParams
	);
	
	if (bHit && HitResult.GetActor())
	{
		return HitResult.GetActor();
	}

	return nullptr;
}

void ASBCharacterExample::Interact()
{
	if(auto* TargetActor = GetActorInFrontOfPlayer())
	{
		if(auto* Interactable = Cast<ISBInteractableInterfaceExample>(TargetActor))
		{
			Interactable->OnInteract(this);
		}
	}
}