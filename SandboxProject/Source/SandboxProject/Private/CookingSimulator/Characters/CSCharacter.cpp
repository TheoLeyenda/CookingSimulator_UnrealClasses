#include "CookingSimulator/Characters/CSCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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

void ACSCharacter::FindActorToInteract(bool& Result, FHitResult& OutHit)
{
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * SphereInteractDistance + Start;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GrabbedActor);
	
	Result = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Start,
		End,
		SphereInteractRadius,
		SphereInteractTraceChannel,
		false,
		IgnoredActors,
		SphereInteractDebugDrawType,
		OutHit,
		false,
		SphereInteractLineColor,
		SphereInteractLineColorHit,
		SphereInteractDrawTime);
}

void ACSCharacter::GrabAndDrop()
{
	bool bHit;
	FHitResult Hit;
	FindActorToInteract(bHit, Hit);

	if(bHit)
	{
		if(auto* InteractInterface = Cast<ICSInteractable>(Hit.GetActor()))
		{
			InteractInterface->GrabAndDrop(this);
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
		FRotator(0,270, 0),
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
	
	FDetachmentTransformRules DetachmentTransformRules = FDetachmentTransformRules(FAttachmentTransformRules::KeepWorldTransform, false);
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
		EnhancedInput->BindAction(GrabDropInputAction, ETriggerEvent::Started, this, &ACSCharacter::GrabAndDrop);
		EnhancedInput->BindAction(StartInteractionInputAction, ETriggerEvent::Started, this, &ACSCharacter::StartInteraction);
		EnhancedInput->BindAction(StopInteractionInputAction, ETriggerEvent::Started, this, &ACSCharacter::StopInteraction);
    }
}

void ACSCharacter::OnGrabMoveFinished(){}

void ACSCharacter::StartInteraction()
{
	if(bIsInteracting)
	{
		StopInteraction();
	}
	else
	{
		bool bResult;
		FHitResult Hit;
		FindActorToInteract(bResult, Hit);
		if(bResult)
		{
			if(auto* InteractInterface = Cast<ICSInteractable>(Hit.GetActor()))
			{
				InteractInterface->Interact(this);
			}
		}
	}
}

void ACSCharacter::StopInteraction()
{
	if(auto* InteractInterface = Cast<ICSInteractable>(InteractingActor))
	{
		InteractInterface->StopInteraction(this);
	}
}

void ACSCharacter::SetIsInteracting(bool InNewValue, AActor* InInteractingActor)
{
	if(!InteractInputMappingContext)
	{
		return;
	}
	bIsInteracting = InNewValue;
	InteractingActor = nullptr;
	
	if(auto* InteractInterface = Cast<ICSInteractable>(InInteractingActor))
	{
		InteractingActor = InInteractingActor;
	}
	
	if(auto* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if(bIsInteracting)
				{
					Subsystem->AddMappingContext(InteractInputMappingContext.Get(),0);
				}
				else
				{
					Subsystem->RemoveMappingContext(InteractInputMappingContext.Get());
				}
			}
		}
	}
}




