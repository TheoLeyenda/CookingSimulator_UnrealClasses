// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSCharacter.generated.h"

class UInputAction;

UCLASS()
class SANDBOXPROJECT_API ACSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACSCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, Category= "Settings|Input")
	TObjectPtr<UInputAction> MovementInputAction = nullptr;

	UFUNCTION()
	void Movement(const FInputActionValue& Value);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
