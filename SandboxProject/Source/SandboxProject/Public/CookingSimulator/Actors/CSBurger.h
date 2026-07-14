// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSComplexFoodItem.h"
#include "CSBurger.generated.h"

UCLASS()
class SANDBOXPROJECT_API ACSBurger : public ACSComplexFoodItem
{
	GENERATED_BODY()
	
public:
	ACSBurger();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	float TopOffsetZ = 20.f; //TODO: Arreglar los meshes (pivot) y quitar el offset
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Component")
	TObjectPtr<UStaticMeshComponent> Top;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TMap<UCSFoodItemDefinition* , ECSFoodItemState> AllowedFoodItems;

	bool IsFoodItemAllowed(ACSFoodItem* FoodItem);
	void AttachFoodItem(ACSFoodItem* FoodItem);
	
public:
	virtual bool TryAddItem(ACSFoodItem* FoodItem) override;
	virtual bool TryAddItems(TArray<ACSFoodItem*> FoodItems) override;
};
