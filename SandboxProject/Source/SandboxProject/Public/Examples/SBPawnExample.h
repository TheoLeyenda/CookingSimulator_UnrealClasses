// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SBPawnExample.generated.h"

class UBoxComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SANDBOXPROJECT_API ASBPawnExample : public APawn
{
	GENERATED_BODY()

public:
	ASBPawnExample();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings|Components")
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings|Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings|Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings|Component")
	class UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Settings|Components")
	class UFloatingPawnMovement* FloatingPawnMovement;
	
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category= "Settings")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
	TObjectPtr<UInputAction> MoveAction;
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
