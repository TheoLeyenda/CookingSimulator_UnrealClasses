#include "CookingSimulator/Assets/DataAssets/CSRecipeDefinition.h"

bool UCSRecipeDefinition::Compare(TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> IngredientsToCompare)
{
	if(Ingredients.Num() != IngredientsToCompare.Num())
	{
		return false;
	}

	for (const TPair<UCSFoodItemDefinition*, FCSRecipeIngredient>& Pair : Ingredients)
	{
		FCSRecipeIngredient* RecipeIngredientA = IngredientsToCompare.Find(Pair.Key);
		if(!RecipeIngredientA)
		{
			return false;
		}

		FCSRecipeIngredient* RecipeIngredientB = Ingredients.Find(Pair.Key);
		
		if(!CompareIngredients(RecipeIngredientA, RecipeIngredientB))
		{
			return false;
		}
	}

	return true;
}

bool UCSRecipeDefinition::CompareIngredients(FCSRecipeIngredient* IngredientA, FCSRecipeIngredient* IngredientB)
{
	if(!IngredientA || !IngredientB)
	{
		return false;
	}
	return IngredientA->State == IngredientB->State && IngredientA->Amount == IngredientB->Amount;
}
