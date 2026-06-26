// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CSFoodItem.generated.h"

UENUM(BlueprintType)
enum class ECSFoodItemState : uint8
{
	Raw,
	Slicing,
	Sliced,
};

UCLASS()
class SANDBOXPROJECT_API ACSFoodItem : public ACSGrabbableActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	bool bIsSlicable = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UMaterial> RawMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UMaterial> SlicedMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UMaterial> SlicingMat;
	
	UFUNCTION(BlueprintCallable)
	void SetState(ECSFoodItemState NewState);

	UFUNCTION(BlueprintPure)
	bool CanBeSliced();
	
protected:
	UPROPERTY()
	ECSFoodItemState State;
};
