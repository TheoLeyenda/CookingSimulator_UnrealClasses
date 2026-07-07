#include "CookingSimulator/Actors/CSStove.h"
#include "CookingSimulator/Interfaces/CSCookwareInterface.h"

ACSStove::ACSStove()
{
	StoveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StoveMesh"));
	StoveMesh->SetupAttachment(StaticMeshComponent.Get());
}


void ACSStove::Grab(ACSCharacter* Character)
{
	if(auto* Cookware = Cast<ICSCookwareInterface>(PlacedActor))
	{
		Cookware->Cook(false);
	}
	Super::Grab(Character);
}

void ACSStove::Place(ACSCharacter* Character)
{
	Super::Place(Character);

	if(auto* Cookware = Cast<ICSCookwareInterface>(PlacedActor))
	{
		Cookware->Cook(true);
	}
}

