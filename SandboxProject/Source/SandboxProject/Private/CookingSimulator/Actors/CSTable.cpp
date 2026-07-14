#include "CookingSimulator/Actors/CSTable.h"

#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CookingSimulator/Characters/CSCharacter.h"

ACSTable::ACSTable()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(Root.Get());

	ActorPlace = CreateDefaultSubobject<USceneComponent>(TEXT("ActorPlace"));
	ActorPlace->SetupAttachment(StaticMeshComponent.Get());
	ActorPlace->SetRelativeLocation(FVector(0,0, 50));
}

void ACSTable::BeginPlay()
{
	Super::BeginPlay();

	if(auto* World = GetWorld())
	{
		if(DefaultPlacedActorClass)
		{
			FActorSpawnParameters ActorSpawnParameters = FActorSpawnParameters();
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			if(auto* SpawnedActor = World->SpawnActor<ACSGrabbableActor>(DefaultPlacedActorClass, ActorPlace->GetComponentTransform(), ActorSpawnParameters))
			{
				AttachActorToPlace(SpawnedActor);
			}
		}
	}
}

bool ACSTable::TryGrab(AActor* Interactor)
{
	if(auto* Interactable = Cast<ICSInteractable>(PlacedActor))
	{
		if(Interactable->TryGrab(Interactor))
		{
			Grab(Cast<ACSCharacter>(Interactor));
			return true;
		}
	}
	return false;
}

void ACSTable::GrabAndDrop(AActor* Interactor)
{
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(!Character->GetGrabbedActor())
		{
			TryGrab(Character);
			return;
		}
		
		if(!PlacedActor)
		{
			Place(Character);
		}
		else
		{
			TryGrab(Character);
		}
	}
}

void ACSTable::Grab(ACSCharacter* Character)
{
	PlacedActor = nullptr;
}

void ACSTable::Place(ACSCharacter* Character)
{
	PlacedActor = Character->GetGrabbedActor();
	AttachActorToPlace(PlacedActor.Get());
	Character->SetGrabbedActor(nullptr);
}

void ACSTable::AttachActorToPlace(ACSGrabbableActor* ActorToPlace)
{
	PlacedActor = ActorToPlace;
	PlacedActor->DisablePhysics();

	FAttachmentTransformRules AttachmentTransformRules =
		FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	PlacedActor->AttachToComponent(ActorPlace.Get(), AttachmentTransformRules);
	PlacedActor->MoveToPlace(FVector::ZeroVector);
}