#include "CookingSimulator/Actors/CSPlateBox.h"
#include "CookingSimulator/Actors/CSPlate.h"
#include "CookingSimulator/Characters/CSCharacter.h"

void ACSPlateBox::BeginPlay()
{
	Super::BeginPlay();
	InitPlates();
}

void ACSPlateBox::InitPlates()
{
	for(int i = 0; i < DefaultPlatesAmount; i++)
	{
		AddPlate();
	}
}

void ACSPlateBox::AddPlate()
{
	if(auto* World = GetWorld())
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = GetInstigator();
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Location = ActorPlace->GetComponentLocation();
		Location.Z = Location.Z + (Plates.Num() * PlateHigh);
		ACSPlate* SpawnedPlate = World->SpawnActor<ACSPlate>(PlateClass, Location, FRotator::ZeroRotator, ActorSpawnParameters);
		if(!SpawnedPlate)
		{
			return;
		}

		SpawnedPlate->DisablePhysics();

		FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
		SpawnedPlate->AttachToComponent(ActorPlace.Get(), AttachmentTransformRules);
		Plates.Add(SpawnedPlate);
	}
}

bool ACSPlateBox::TryGrab(AActor* Interactor)
{
	if(Plates.IsEmpty())
	{
		return false;
	}

	if(auto* LastPlate = Plates[Plates.Num() - 1])
	{
		if(auto* Interactable = Cast<ICSInteractable>(LastPlate))
		{
			if(Interactable->TryGrab(Interactor))
			{
				Grab(Cast<ACSCharacter>(Interactor));
				return true;
			}
		}
	}

	return false;
}

void ACSPlateBox::GrabAndDrop(AActor* Interactor)
{
	TryGrab(Interactor);
}

void ACSPlateBox::Grab(ACSCharacter* Character)
{
	if(!Character)
	{
		return;
	}
	
	ACSPlate* Plate = Plates[Plates.Num() - 1];
	if(!Plate)
	{
		return;
	}
	
	Plates.Remove(Plate);
}


