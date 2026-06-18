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

void ACSTable::Interact(AActor* Interactor)
{
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(!Character->GetGrabbedActor())
		{
			Character->Grab(PlacedActor.Get());
			PlacedActor = nullptr;
			return;
		}
		
		if(!PlacedActor)
		{
			PlacedActor = Character->GetGrabbedActor();
			FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
			PlacedActor->AttachToComponent(ActorPlace.Get(), AttachmentTransformRules);

			FLatentActionInfo LatentActionInfo;
			LatentActionInfo.CallbackTarget = this;
			LatentActionInfo.ExecutionFunction = FName("OnPlaceActorOnTableDone");
			LatentActionInfo.Linkage = 0;
			LatentActionInfo.UUID = 1;

			UKismetSystemLibrary::MoveComponentTo(
				PlacedActor->GetRootComponent(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				false,
				false,
				0.2f,
				false,
				EMoveComponentAction::Type::Move,
				LatentActionInfo);

			Character->SetGrabbedActor(nullptr);
		}
	}
}

void ACSTable::OnPlaceActorOnTableDone(){}



