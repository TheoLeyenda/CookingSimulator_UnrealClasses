// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CookingSimulator/Interfaces/CSInteractable.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CSCharacter.generated.h"

class UInputMappingContext;
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

	UFUNCTION(BlueprintCallable)
	void SetIsInteracting(bool InNewValue, AActor* InInteractingActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Settings|Input")
	TObjectPtr<UInputMappingContext> InteractInputMappingContext = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> MovementInputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> GrabDropInputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> StartInteractionInputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> StopInteractionInputAction = nullptr;
	
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

	UPROPERTY(VisibleAnywhere)
	ACSGrabbableActor* GrabbedActor;

	UPROPERTY()
	AActor* InteractingActor = nullptr;
	
	UPROPERTY()
	bool bIsInteracting = false;
	
	UFUNCTION()
	void Movement(const FInputActionValue& Value);

	UFUNCTION()
	void GrabAndDrop();

	UFUNCTION()
	void StartInteraction();

	UFUNCTION()
	void StopInteraction();
	
	UFUNCTION()
	void FindActorToInteract(bool& Result, FHitResult& OutHit);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void OnGrabMoveFinished();
};
