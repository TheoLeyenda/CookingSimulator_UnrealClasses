// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBMacrosExampleActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS()
class SANDBOXPROJECT_API ASBMacrosExampleActor : public AActor
{
	GENERATED_BODY()
public:
	ASBMacrosExampleActor();
	
	UPROPERTY(BlueprintSetter=SetFloatValue)
	float SetterFloatValue = 0.0f;
	
	UFUNCTION(BlueprintCallable)
	void SetFloatValue(float NewValue) { SetterFloatValue = NewValue * 2; }

	UPROPERTY(BlueprintGetter=GetFloatValue)
	float GetterFloatValue = 0.0f;
	
	UFUNCTION(BlueprintPure)
	float GetFloatValue() { return GetterFloatValue + 20.0; }

	UFUNCTION(BlueprintPure)
	float CalculateSpeed(){ return 0.0f; }

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

	UFUNCTION(BlueprintCallable)
	void Jump(){}

	UFUNCTION(BlueprintImplementableEvent)
	void Death();

	UFUNCTION(BlueprintCallable, Category="Combat")
	void Attack(){}
	

};
