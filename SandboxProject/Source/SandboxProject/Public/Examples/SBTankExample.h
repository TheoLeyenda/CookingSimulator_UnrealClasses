// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBTankExample.generated.h"

UCLASS()
class SANDBOXPROJECT_API ASBTankExample : public AActor
{
	GENERATED_BODY()

public:
	ASBTankExample();
	
protected:
	// El chasis será la base del tanque
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* ChassisMesh;

	// La torreta se enganchará sobre el chasis para rotar sola
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* TurretMesh;

	//Cañon de la torreta.
	UPROPERTY(VisibleAnywhere, Category= "Components")
	class UStaticMeshComponent* Cannon;
	
	// Un USceneComponent vacío que usaremos como "puntero" o "puerto" espacial para saber dónde spawnear las balas
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* BarrelMuzzleLocation;
};
