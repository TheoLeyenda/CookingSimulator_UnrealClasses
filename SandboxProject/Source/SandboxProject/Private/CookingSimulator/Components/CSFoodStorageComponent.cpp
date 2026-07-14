#include "CookingSimulator/Components/CSFoodStorageComponent.h"

#include "CookingSimulator/Actors/CSComplexFoodItem.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Data/CSStructsTypes.h"

UCSFoodStorageComponent::UCSFoodStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UCSFoodStorageComponent::HasPlace(int32 NewItemsAmount)
{
	return MaxFoodItemsCount - Items.Num() >= NewItemsAmount;
}

bool UCSFoodStorageComponent::TryAddItem(ACSFoodItem* FoodItem)
{
	if(HasPlace(1))
	{
		Items.Add(FoodItem);
		FoodItem->DisablePhysics();
		return true;
	}
	return false;
}

bool UCSFoodStorageComponent::TryAddItems(TArray<ACSFoodItem*> FoodItems)
{
	if(HasPlace(FoodItems.Num()))
	{
		Items.Append(FoodItems);
		return true;
	}
	return false;
}

TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> UCSFoodStorageComponent::GetIngredients()
{
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> PlateIngredients = TMap<UCSFoodItemDefinition*, FCSRecipeIngredient>();
	for (auto Element : Items)
	{
		if(auto* ComplexFoodItem = Cast<ACSComplexFoodItem>(Element))
		{
			TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> ComplexIngredients = ComplexFoodItem->GetIngredients();
			TArray<UCSFoodItemDefinition*> Keys;
			ComplexIngredients.GetKeys(Keys);
			for (auto Key : Keys)
			{
				UpdateIngredients(PlateIngredients, Key, ComplexIngredients.Find(Key)->State, ComplexIngredients.Find(Key)->Amount);
			}
		}
		else
		{
			UpdateIngredients(PlateIngredients, Element->GetFoodItemDefinition(), Element->GetState());
		}
	}

	return PlateIngredients;
}

void UCSFoodStorageComponent::UpdateIngredients(
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient>& PlateIngredients,
	UCSFoodItemDefinition* ItemDefinition,
	ECSFoodItemState FoodItemState,
	int32 Amount)
{
	if(FCSRecipeIngredient* FoundItem = PlateIngredients.Find(ItemDefinition))
	{
		FCSRecipeIngredient RecipeIngredient = FCSRecipeIngredient();
		RecipeIngredient.State = FoundItem->State;
		RecipeIngredient.Amount = FoundItem->Amount + Amount;
		PlateIngredients.Add(ItemDefinition, RecipeIngredient);
	}
	else
	{
		FCSRecipeIngredient RecipeIngredient = FCSRecipeIngredient();
		RecipeIngredient.State = FoodItemState;
		RecipeIngredient.Amount = Amount;
		PlateIngredients.Add(ItemDefinition, RecipeIngredient);
	}
}

void UCSFoodStorageComponent::DestroyItems()
{
	for (auto Element : Items)
	{
		Element->Destroy();
	}
	Items.Empty();
}
