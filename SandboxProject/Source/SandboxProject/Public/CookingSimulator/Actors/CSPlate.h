#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSKitchenware.h"
#include "CSPlate.generated.h"

UCLASS()
class SANDBOXPROJECT_API ACSPlate : public ACSKitchenware
{
	GENERATED_BODY()

protected:
	virtual void AddItem(ACSFoodItem* FoodItem) override;
};
