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

protected:
	virtual void AddItem(ACSFoodItem* FoodItem) override;

public:
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> GetIngredients();
};
