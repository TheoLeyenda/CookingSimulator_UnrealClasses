#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CSStructsTypes.generated.h"

USTRUCT(BlueprintType)
struct FCSRecipeIngredient
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECSFoodItemState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};
