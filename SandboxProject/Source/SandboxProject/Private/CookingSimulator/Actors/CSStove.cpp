#include "CookingSimulator/Actors/CSStove.h"
#include "CookingSimulator/Interfaces/CSCookwareInterface.h"

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

