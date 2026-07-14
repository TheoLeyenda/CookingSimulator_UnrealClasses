// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CookingSimulator/Interfaces/CSDishInterface.h"
#include "CSFoodStorageComponent.generated.h"


enum class ECSFoodItemState : uint8;
class UCSFoodItemDefinition;
struct FCSRecipeIngredient;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOXPROJECT_API UCSFoodStorageComponent : public UActorComponent, public ICSDishInterface
{
	GENERATED_BODY()

public:	
	UCSFoodStorageComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TArray<ACSFoodItem*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	int32 MaxFoodItemsCount = 4;

	UFUNCTION()
	bool HasPlace(int32 NewItemsAmount);

	virtual bool TryAddItem(ACSFoodItem* FoodItem) override;
	virtual bool TryAddItems(TArray<ACSFoodItem*> FoodItems) override;

	TMap<UCSFoodItemDefinition*, FCSRecipeIngredient> GetIngredients();

	void UpdateIngredients(TMap<UCSFoodItemDefinition*, FCSRecipeIngredient>& PlateIngredients, UCSFoodItemDefinition* ItemDefinition, ECSFoodItemState FoodItemState, int32 Amount = 1);

	void DestroyItems();
};
