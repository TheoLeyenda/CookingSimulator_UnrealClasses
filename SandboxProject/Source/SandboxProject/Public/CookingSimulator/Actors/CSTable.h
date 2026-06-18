// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Interfaces/CSInteractable.h"
#include "GameFramework/Actor.h"
#include "CSTable.generated.h"

class ACSGrabbableActor;

UCLASS()
class SANDBOXPROJECT_API ACSTable : public AActor, public ICSInteractable
{
	GENERATED_BODY()
	
public:	
	ACSTable();

	UPROPERTY(EditAnywhere, Category= "Components")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditAnywhere, Category= "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category= "Components")
	TObjectPtr<USceneComponent> ActorPlace;

	UPROPERTY(VisibleAnywhere, Category= "Settings")
	TObjectPtr<ACSGrabbableActor> PlacedActor;

	virtual void Interact(AActor* Interactor) override;

	UFUNCTION()
	void OnPlaceActorOnTableDone();
};
