// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSTable.h"
#include "CSPlateBox.generated.h"

class ACSPlate;

UCLASS()
class SANDBOXPROJECT_API ACSPlateBox : public ACSTable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	int32 DefaultPlatesAmount = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	float PlateHigh = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TSubclassOf<ACSPlate> PlateClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings")
	TArray<ACSPlate*> Plates;

	virtual void BeginPlay() override;
	
	void InitPlates();

public:
	virtual void GrabAndDrop(AActor* Interactor) override;
	virtual void Grab(ACSCharacter* Character) override;
};
