// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SBInteractableInterfaceExample.generated.h"

UINTERFACE(MinimalAPI)
class USBInteractableInterfaceExample : public UInterface
{
	GENERATED_BODY()
};

class SANDBOXPROJECT_API ISBInteractableInterfaceExample
{
	GENERATED_BODY()
public:
	//Implementacion obligatoria.
	virtual void OnInteract(AActor* Interactor) = 0;
};
