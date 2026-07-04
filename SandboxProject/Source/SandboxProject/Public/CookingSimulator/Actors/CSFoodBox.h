#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSTable.h"
#include "CSFoodBox.generated.h"

class UCSFoodItemDefinition;
class ACSFoodItem;

UCLASS()
class SANDBOXPROJECT_API ACSFoodBox : public ACSTable
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UCSFoodItemDefinition> FoodItemDefinition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TSubclassOf<ACSFoodItem> FoodItemClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UMaterialInterface> FoodMaterial;
	
	virtual void GrabAndDrop(AActor* Interactor) override;

protected:
	void UpdateMaterial();
	
	#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    #endif
};
