#include "CookingSimulator/Actors/CSPlate.h"

#include "CookingSimulator/Actors/CSFoodItem.h"

void ACSPlate::AddItem(ACSFoodItem* FoodItem)
{
	Super::AddItem(FoodItem);
	if(!FoodItem)
	{
		return;
	}

	FoodItem->SetState(ECSFoodItemState::OnPlate);
}
