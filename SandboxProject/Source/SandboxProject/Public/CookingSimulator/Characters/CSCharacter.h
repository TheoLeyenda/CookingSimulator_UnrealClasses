// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CSCharacter.generated.h"

class ACSGrabbableActor;
class UInputAction;

UCLASS()
class SANDBOXPROJECT_API ACSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACSCharacter();

	UFUNCTION(BlueprintCallable)
	void SetGrabbedActor(ACSGrabbableActor* NewGrabbedActor) { GrabbedActor = NewGrabbedActor; }
	
	UFUNCTION(BlueprintPure)
	ACSGrabbableActor* GetGrabbedActor(){ return GrabbedActor; }

	UFUNCTION(BlueprintCallable)
	void Grab(ACSGrabbableActor* ActorToGrab);

	UFUNCTION(BlueprintCallable)
	void Drop();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> MovementInputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> InteractInputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Interact")
	float SphereInteractDistance = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Interact")
	float SphereInteractRadius = 60.0f;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Interact")
	TEnumAsByte<ETraceTypeQuery> SphereInteractTraceChannel;

	UPROPERTY(EditAnywhere, Category= "Settings|Interact|Debug")
	TEnumAsByte<EDrawDebugTrace::Type> SphereInteractDebugDrawType;

	UPROPERTY(EditAnywhere, Category= "Settings|Interact|Debug")
	FLinearColor SphereInteractLineColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, Category= "Settings|Interact|Debug")
	FLinearColor SphereInteractLineColorHit = FLinearColor::Green;

	UPROPERTY(EditAnywhere, Category= "Settings|Interact|Debug")
	float SphereInteractDrawTime = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category= "Settings|Components")
	TObjectPtr<USceneComponent> Hands;

	UPROPERTY()
	ACSGrabbableActor* GrabbedActor;
	
	UFUNCTION()
	void Movement(const FInputActionValue& Value);

	UFUNCTION()
	void Interact();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void OnGrabMoveFinished();
};
