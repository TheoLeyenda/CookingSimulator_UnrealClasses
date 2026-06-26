// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CSPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SANDBOXPROJECT_API ACSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings|Input")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext = nullptr;
	
	UPROPERTY(EditAnywhere, Category= "Settings|Camera")
	FTransform CameraActorTransform;
	
	UPROPERTY(EditAnywhere, Category= "Settings|Camera")
	TSubclassOf<ACameraActor> CameraActorClass = nullptr;

	UPROPERTY()
	TObjectPtr<ACameraActor> CameraActor;
	
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	ACameraActor* GetCameraActor(){ return CameraActor.Get(); }
};
