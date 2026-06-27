#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "Components/BoxComponent.h"
#include "CookingSimulator/Characters/CSCharacter.h"

ACSGrabbableActor::ACSGrabbableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetupAttachment(StaticMeshComponent.Get());
	BoxComponent->SetBoxExtent(FVector(20.0f));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetMassOverrideInKg(NAME_None, 1000, true);
	BoxComponent->SetCollisionProfileName("BlockAllDynamic");
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(BoxComponent.Get());
	StaticMeshComponent->SetRelativeScale3D(FVector(0.4f));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void ACSGrabbableActor::GrabAndDrop(AActor* Interactor)
{
	Grab(Cast<ACSCharacter>(Interactor));
}

void ACSGrabbableActor::Grab(ACSCharacter* Character)
{
	if(CanBeGrabbed(Character))
	{
		DisablePhysics();
		Character->Grab(this);
	}
}

void ACSGrabbableActor::Drop()
{
	EnablePhysics();
}

bool ACSGrabbableActor::CanBeGrabbed(ACSCharacter* Character) const
{
	if(!Character)
	{
		return false;
	}
	
	return !Character->GetGrabbedActor();
}

void ACSGrabbableActor::DisablePhysics()
{
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACSGrabbableActor::EnablePhysics()
{
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}


