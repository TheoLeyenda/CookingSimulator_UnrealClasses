// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Actors/CSTable.h"
#include "CSTableWithSlicingPlace.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API ACSTableWithSlicingPlace : public ACSTable
{
	GENERATED_BODY()

public:
	ACSTableWithSlicingPlace();
	virtual void GrabAndDrop(AActor* Interactor) override;
	virtual void Interact(AActor* Interactor) override;
	virtual void StopInteraction(AActor* Interactor) override;
	bool CanGrabActor() const { return Progress == 0 || Progress == 1;}

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, Category= "Settings|Debug")
	bool bShowProgress = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	float SlicingSpeed = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UStaticMeshComponent> SlicingPlaceMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UStaticMeshComponent> KnifeMesh;
	
	UPROPERTY()
	float Progress = 0;
	
	UPROPERTY()
	bool bIsInteracting = false;
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentInteractor = nullptr;
};
