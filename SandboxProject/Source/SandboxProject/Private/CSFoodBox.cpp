#include "CSFoodBox.h"

#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CookingSimulator/Characters/CSCharacter.h"

void ACSFoodBox::GrabAndDrop(AActor* Interactor)
{
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(PlacedActor)
		{
			if(PlacedActor->CanBeGrabbed(Character))
			{
				Super::GrabAndDrop(Character);
			}
		}
		else if(Character->GetGrabbedActor())
		{
			Super::GrabAndDrop(Character);
		}
		else
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
			ActorSpawnParameters.Instigator = GetInstigator();
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			ACSFoodItem* FoodItem = GetWorld()->SpawnActor<ACSFoodItem>(FoodItemClass, GetActorTransform(), ActorSpawnParameters);
			if(FoodItem)
			{
				FoodItem->bIsSlicable = true;
				FoodItem->GrabAndDrop(Character);
			}
		}
	}
}
