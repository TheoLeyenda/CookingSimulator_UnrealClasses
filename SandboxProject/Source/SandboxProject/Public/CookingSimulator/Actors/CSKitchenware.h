// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CookingSimulator/Interfaces/CSDishInterface.h"
#include "CSKitchenware.generated.h"

class UCSFoodStorageComponent;
/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API ACSKitchenware : public ACSGrabbableActor, public ICSDishInterface
{
	GENERATED_BODY()

public:
	ACSKitchenware();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Components")
	TObjectPtr<USceneComponent> FoodPlace; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Components")
	TObjectPtr<UCSFoodStorageComponent> FoodStorageComponent;
	
	bool HasPlace(int32 NewItemsAmount = 1) const;
	bool IsEmpty() const;

	virtual bool TryGrab(AActor* Interactor) override;
	virtual bool TryAddItem(ACSFoodItem* FoodItem) override;
	virtual bool TryAddItems(TArray<ACSFoodItem*> InFoodItems) override;
	virtual void TryAddItemsToComplex(ACSFoodItem* FoodItem, bool& ShouldAddToKitchen, bool& Added);
	
	void AttachFoodItem(ACSFoodItem* FoodItem);

	TArray<ACSFoodItem*>& GetFoodItems() const;
	void ClearFoodItems();
	
	virtual void Destroyed() override;
};
