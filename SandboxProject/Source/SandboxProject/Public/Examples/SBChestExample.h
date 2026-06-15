// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBInteractableInterfaceExample.h"
#include "GameFramework/Actor.h"
#include "SBChestExample.generated.h"

UCLASS()
class SANDBOXPROJECT_API ASBChestExample : public AActor, public ISBInteractableInterfaceExample
{
	GENERATED_BODY()
	
public:	
	ASBChestExample();

protected:
	virtual void OnInteract(AActor* Interactor) override;
};
