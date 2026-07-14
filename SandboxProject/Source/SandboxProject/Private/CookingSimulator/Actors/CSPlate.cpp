#include "CookingSimulator/Actors/CSPlate.h"

#include "CookingSimulator/Actors/CSComplexFoodItem.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Components/CSFoodStorageComponent.h"

bool ACSPlate::TryAddItem(ACSFoodItem* FoodItem)
{
	bool Exist;
	TObjectPtr<ACSFoodItem> ComplexFoodItem;
	IsComplexItemInside(Exist, ComplexFoodItem);

	if(Exist)
	{
		if(auto* DishInterface = Cast<ICSDishInterface>(ComplexFoodItem))
		{
			return DishInterface->TryAddItem(FoodItem);
		}
	}
	return Super::TryAddItem(FoodItem);
}

bool ACSPlate::TryAddItems(TArray<ACSFoodItem*> FoodItems)
{
	bool Exist;
	TObjectPtr<ACSFoodItem> ComplexFoodItem;
	IsComplexItemInside(Exist, ComplexFoodItem);

	if(Exist)
	{
		if(auto* DishInterface = Cast<ICSDishInterface>(ComplexFoodItem))
		{
			return DishInterface->TryAddItems(FoodItems);
		}
	}
	return Super::TryAddItems(FoodItems);
}

void ACSPlate::TryAddItemsToComplex(ACSFoodItem* FoodItem, bool& ShouldAddToKitchen, bool& Added)
{
	Super::TryAddItemsToComplex(FoodItem, ShouldAddToKitchen, Added);

	if(Added)
	{
		ShouldAddToKitchen = true;
	}
	else
	{
		ShouldAddToKitchen = false;
	}
}

TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> ACSPlate::GetIngredients()
{
	return FoodStorageComponent->GetIngredients();
}

void ACSPlate::IsComplexItemInside(bool& Exist, TObjectPtr<ACSFoodItem>& ComplexFoodItem)
{
	if(IsEmpty())
	{
		Exist = false;
		ComplexFoodItem = nullptr;
	}
	else if(ACSComplexFoodItem* InternalComplexFoodItem = Cast<ACSComplexFoodItem>(GetFoodItems()[0]))
	{
		Exist = true;
		ComplexFoodItem = InternalComplexFoodItem;
	}
	else
	{
		Exist = false;
		ComplexFoodItem = nullptr;
	}
}
