#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSKitchenware.h"
#include "CookingSimulator/Data/CSStructsTypes.h"
#include "CSPlate.generated.h"

class UCSFoodItemDefinition;

UCLASS()
class SANDBOXPROJECT_API ACSPlate : public ACSKitchenware
{
	GENERATED_BODY()

public:
	virtual bool TryAddItem(ACSFoodItem* FoodItem) override;
	virtual bool TryAddItems(TArray<ACSFoodItem*> FoodItems) override;
	virtual void TryAddItemsToComplex(ACSFoodItem* FoodItem, bool& ShouldAddToKitchen, bool& Added) override;
	virtual void IsComplexItemInside(bool& Exist, TObjectPtr<ACSFoodItem>& ComplexFoodItem);
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> GetIngredients();
};
