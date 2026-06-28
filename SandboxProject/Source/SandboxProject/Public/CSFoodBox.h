#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSTable.h"
#include "CSFoodBox.generated.h"

class ACSFoodItem;

UCLASS()
class SANDBOXPROJECT_API ACSFoodBox : public ACSTable
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TSubclassOf<ACSFoodItem> FoodItemClass;
	
	virtual void GrabAndDrop(AActor* Interactor) override;
};
