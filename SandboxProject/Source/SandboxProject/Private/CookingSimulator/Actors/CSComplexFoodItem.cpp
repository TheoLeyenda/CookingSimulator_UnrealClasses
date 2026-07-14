#include "CookingSimulator/Actors/CSComplexFoodItem.h"

#include "CookingSimulator/Characters/CSCharacter.h"
#include "CookingSimulator/Components/CSFoodStorageComponent.h"
#include "CookingSimulator/Data/CSStructsTypes.h"

ACSComplexFoodItem::ACSComplexFoodItem()
{
	FoodStorageComponent = CreateDefaultSubobject<UCSFoodStorageComponent>(TEXT("FoodStorageComponent"));
}

bool ACSComplexFoodItem::TryGrab(AActor* Interactor)
{
	if(Super::TryGrab(Interactor))
	{
		return true;
	}

	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(auto* FoodItem = Cast<ACSFoodItem>(Character->GetGrabbedActor()))
		{
			if(TryAddItem(FoodItem))
			{
				Character->SetGrabbedActor(nullptr);
				Grab(Character);
				return true;
			}
		}
	}

	return false;
}

bool ACSComplexFoodItem::TryAddItem(ACSFoodItem* FoodItem)
{
	return FoodStorageComponent->TryAddItem(FoodItem);
}

bool ACSComplexFoodItem::TryAddItems(TArray<ACSFoodItem*> FoodItems)
{
	return FoodStorageComponent->TryAddItems(FoodItems);	
}

TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> ACSComplexFoodItem::GetIngredients()
{
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> Ingredients = FoodStorageComponent->GetIngredients();
	
	FCSRecipeIngredient RecipeIngredient;
	RecipeIngredient.Amount = 1;
	RecipeIngredient.State = State;
	
	Ingredients.Add(FoodItemDefinition, RecipeIngredient);
	
	return Ingredients;
}

void ACSComplexFoodItem::Destroyed()
{
	FoodStorageComponent->DestroyItems();
	Super::Destroyed();
}