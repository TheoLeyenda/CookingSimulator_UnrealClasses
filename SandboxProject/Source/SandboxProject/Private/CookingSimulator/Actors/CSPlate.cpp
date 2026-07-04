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

TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> ACSPlate::GetIngredients()
{
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> PlateIngredients;

	for (auto Element : FoodItems)
	{
		if(FCSRecipeIngredient* FoundItem = PlateIngredients.Find(Element->GetFoodItemDefinition()))
		{
			FCSRecipeIngredient RecipeIngredient = FCSRecipeIngredient();
			RecipeIngredient.State = FoundItem->State;
			RecipeIngredient.Amount = FoundItem->Amount + 1;
			PlateIngredients.Add(Element->GetFoodItemDefinition(), RecipeIngredient);
		}
		else
		{
			FCSRecipeIngredient RecipeIngredient = FCSRecipeIngredient();
			RecipeIngredient.State = Element->GetState();
			RecipeIngredient.Amount = 1;
			PlateIngredients.Add(Element->GetFoodItemDefinition(), RecipeIngredient);
		}
	}

	return PlateIngredients;
}
