// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBInteractableInterfaceExample.h"
#include "GameFramework/Actor.h"
#include "SBCarExample.generated.h"

UCLASS()
class SANDBOXPROJECT_API ASBCarExample : public AActor, public ISBInteractableInterfaceExample
{
	GENERATED_BODY()
	
public:	
	ASBCarExample();

protected:
	virtual void OnInteract(AActor* Interactor) override;
};
