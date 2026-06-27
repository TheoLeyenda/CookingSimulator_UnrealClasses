// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CookingSimulator/Interfaces/CSDishInterface.h"
#include "CSDish.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API ACSDish : public ACSGrabbableActor, public ICSDishInterface
{
	GENERATED_BODY()

public:
	ACSDish();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Components")
	TObjectPtr<USceneComponent> FoodPlace; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings", meta = (ClampMin = 1, ClampMax = 5))
	int32 MaxItemsCount = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings")
	TArray<ACSFoodItem*> FoodItems;
	
	bool HasPlace() const;

	virtual void AddItem(ACSFoodItem* FoodItem) override;

protected:
	UFUNCTION()
	void OnPlaceFoodOnDishDone();
};
