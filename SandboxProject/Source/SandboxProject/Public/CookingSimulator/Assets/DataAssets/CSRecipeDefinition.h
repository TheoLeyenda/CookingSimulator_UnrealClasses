// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSFoodItemDefinition.h"
#include "CookingSimulator/Data/CSStructsTypes.h"
#include "Engine/DataAsset.h"
#include "CSRecipeDefinition.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API UCSRecipeDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> Ingredients;

	bool Compare(TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> IngredientsToCompare);
	bool CompareIngredients(FCSRecipeIngredient* IngredientA, FCSRecipeIngredient* IngredientB);
};
