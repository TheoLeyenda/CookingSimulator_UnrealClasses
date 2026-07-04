// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CSFoodItem.generated.h"

class UCSFoodItemDefinition;

UENUM(BlueprintType)
enum class ECSFoodItemState : uint8
{
	Raw,
	Slicing,
	Sliced,
	OnPlate,
};

UCLASS()
class SANDBOXPROJECT_API ACSFoodItem : public ACSGrabbableActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	bool bIsSlicable = true;

	void SetFoodItemDefinition(UCSFoodItemDefinition* InFoodItemDefinition);
	
	UCSFoodItemDefinition* GetFoodItemDefinition() const;
	
	UFUNCTION(BlueprintCallable)
	void SetState(ECSFoodItemState NewState);

	ECSFoodItemState GetState() const;
	
	UFUNCTION(BlueprintPure)
	bool CanBeSliced();

	virtual bool CanBeGrabbed(ACSCharacter* Character) const override;
	virtual void Grab(ACSCharacter* Character) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UCSFoodItemDefinition> FoodItemDefinition;
	
	UPROPERTY()
	ECSFoodItemState State;
};
