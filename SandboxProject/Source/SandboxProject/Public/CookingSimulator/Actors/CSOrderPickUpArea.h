// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Assets/DataAssets/CSRecipeDefinition.h"
#include "CookingSimulator/Interfaces/CSInteractable.h"
#include "GameFramework/Actor.h"
#include "CSOrderPickUpArea.generated.h"

class ACSPlateBox;

UCLASS()
class SANDBOXPROJECT_API ACSOrderPickUpArea : public AActor, public ICSInteractable
{
	GENERATED_BODY()
	
public:	
	ACSOrderPickUpArea();

	virtual void BeginPlay() override;
	
	virtual void GrabAndDrop(AActor* Interactor) override;

	ACSPlateBox* GetCurrentPlateBox() const;
	
	UPROPERTY()
	TArray<ACSPlateBox*> AllPlateBoxes;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<UCSRecipeDefinition> RecipeForTest;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TObjectPtr<ACSPlateBox> ConnectedPlateBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Settings")
	TSubclassOf<AActor> PlateBoxClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Components")
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
