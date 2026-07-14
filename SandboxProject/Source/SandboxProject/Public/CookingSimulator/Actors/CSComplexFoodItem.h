#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Interfaces/CSDishInterface.h"
#include "CSComplexFoodItem.generated.h"

struct FCSRecipeIngredient;
class UCSFoodStorageComponent;
/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API ACSComplexFoodItem : public ACSFoodItem, public ICSDishInterface
{
	GENERATED_BODY()

public:
	ACSComplexFoodItem();

	virtual bool TryGrab(AActor* Interactor) override;
	virtual bool TryAddItem(ACSFoodItem* FoodItem) override;
	virtual bool TryAddItems(TArray<ACSFoodItem*> FoodItems) override;
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> GetIngredients();
	virtual void Destroyed() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCSFoodStorageComponent> FoodStorageComponent;
};
