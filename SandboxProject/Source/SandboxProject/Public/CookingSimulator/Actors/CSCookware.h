// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSKitchenware.h"
#include "CookingSimulator/Interfaces/CSCookwareInterface.h"
#include "CSCookware.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API ACSCookware : public ACSKitchenware, public ICSCookwareInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings")
	bool bIsCooking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	int32 CookingScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	int32 CookingTargetScorePerItem = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	float UpdateCookingProgressRate = 0.2f;

	UPROPERTY()
	FTimerHandle UpdateCookingProgressHandle;
	
	virtual void Cook(bool bEnable) override;

	UFUNCTION()
	virtual void OnCooked();
	
	UFUNCTION()
	void UpdateCookingProgress();
	
	void SendUpdateCookingProgressTimer();
};
