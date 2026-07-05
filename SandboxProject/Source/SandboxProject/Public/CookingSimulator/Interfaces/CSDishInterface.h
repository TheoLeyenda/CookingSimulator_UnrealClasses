#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CSDishInterface.generated.h"

class ACSFoodItem;

UINTERFACE(MinimalAPI)
class UCSDishInterface : public UInterface
{
	GENERATED_BODY()
};


class SANDBOXPROJECT_API ICSDishInterface
{
	GENERATED_BODY()

public:
	virtual bool TryAddItem(ACSFoodItem* FoodItem){ return true; }
	virtual bool TryAddItems(TArray<ACSFoodItem*> FoodItems) { return true; }
};
