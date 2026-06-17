#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "Components/SphereComponent.h"
#include "CookingSimulator/Characters/CSCharacter.h"

ACSGrabbableActor::ACSGrabbableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	SphereComponent->SetupAttachment(StaticMeshComponent.Get());
	SphereComponent->SetSphereRadius(21.5f);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetMassOverrideInKg(NAME_None, 100, true);
	SphereComponent->SetCollisionProfileName("BlockAllDynamic");
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SphereComponent.Get());
	StaticMeshComponent->SetRelativeScale3D(FVector(0.4f));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void ACSGrabbableActor::Interact(AActor* Interactor)
{
	Grab(Cast<ACSCharacter>(Interactor));
}

void ACSGrabbableActor::Grab(ACSCharacter* Character)
{
	if(!Character)
	{
		return;
	}
	
	if(!Character->GetGrabbedActor())
	{
		SphereComponent->SetSimulatePhysics(false);
		Character->Grab(this);
	}
}

void ACSGrabbableActor::Drop()
{
	SphereComponent->SetSimulatePhysics(true);
}



