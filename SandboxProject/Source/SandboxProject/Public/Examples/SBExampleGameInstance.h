// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SBExampleGameInstance.generated.h"


UCLASS()
class SANDBOXPROJECT_API USBExampleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	//Esta variable sobrevivira a los cambios de mapa.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Player Data")
	int32 GlobalScore = 0;
};
