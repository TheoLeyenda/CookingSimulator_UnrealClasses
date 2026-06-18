#include "CookingSimulator/Characters/CSCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CookingSimulator/Interfaces/CSInteractable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ACSCharacter::ACSCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	Hands = CreateDefaultSubobject<USceneComponent>(TEXT("Hands"));
	Hands->SetupAttachment(GetCapsuleComponent());
	Hands->SetRelativeLocation(FVector(70, 0, 0));
}

void ACSCharacter::Movement(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(FVector(MovementVector.X, MovementVector.Y, 0), 1);
}

void ACSCharacter::Interact()
{
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * SphereInteractDistance + Start;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GrabbedActor);
	
	const bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Start,
		End,
		SphereInteractRadius,
		SphereInteractTraceChannel,
		false,
		IgnoredActors,
		SphereInteractDebugDrawType,
		Hit,
		false,
		SphereInteractLineColor,
		SphereInteractLineColorHit,
		SphereInteractDrawTime);

	if(bHit)
	{
		if(auto* InteractInterface = Cast<ICSInteractable>(Hit.GetActor()))
		{
			InteractInterface->Interact(this);
		}
	}
	else if(GrabbedActor)
	{
		Drop();
	}
}

void ACSCharacter::Grab(ACSGrabbableActor* ActorToGrab)
{
	if(!ActorToGrab)
	{
		return;	
	}
	GrabbedActor = ActorToGrab;

	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName("OnGrabMoveFinished");
	LatentActionInfo.Linkage = 0;
	LatentActionInfo.UUID = 1;
	
	FAttachmentTransformRules AttachmentRule = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	GrabbedActor->AttachToComponent(Hands, AttachmentRule);

	UKismetSystemLibrary::MoveComponentTo(
		GrabbedActor->GetRootComponent(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		false,
		false,
		0.2f,
		false,
		EMoveComponentAction::Type::Move, LatentActionInfo);
}

void ACSCharacter::Drop()
{
	if(!GrabbedActor)
	{
		return;
	}
	
	FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules(FAttachmentTransformRules::KeepRelativeTransform, false);
	GrabbedActor->DetachFromActor(DetachmentTransformRules);
	GrabbedActor->Drop();
	GrabbedActor = nullptr;
}

void ACSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
    	EnhancedInput->BindAction(MovementInputAction, ETriggerEvent::Triggered,this,&ACSCharacter::Movement);
		EnhancedInput->BindAction(InteractInputAction, ETriggerEvent::Started, this, &ACSCharacter::Interact);
    }
}

void ACSCharacter::OnGrabMoveFinished(){}

