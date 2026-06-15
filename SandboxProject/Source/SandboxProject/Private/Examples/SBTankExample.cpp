#include "Examples/SBTankExample.h"

#include "Examples/SBExampleGameInstance.h"

ASBTankExample::ASBTankExample()
{
	PrimaryActorTick.bCanEverTick = false;

	// 1. Creamos el chasis y lo definimos como la Raíz del Actor
	ChassisMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChassisMesh"));
	RootComponent = ChassisMesh; 

	// 2. Creamos la torreta
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(RootComponent); 

	// Opcional: Ajustamos su posición relativa para que quede encima del chasis
	TurretMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	//3. Creamos el cañon.
	Cannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon"));
	Cannon->SetupAttachment(TurretMesh);
	Cannon->SetRelativeLocation(FVector(60.0f, 0.0f, 20.0f));
	Cannon->SetRelativeRotation(FRotator(90, 0, 0));
	Cannon->SetRelativeScale3D(FVector(0.25, 0.25, 1));
	
	// 3. Creamos el punto de salida de la bala (un componente de escena puro, sin malla visual)
	BarrelMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    
	// Enganchamos la punta del cañón a la torreta (si la torreta gira, la punta gira con ella)
	BarrelMuzzleLocation->SetupAttachment(Cannon);
	BarrelMuzzleLocation->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f)); // Adelante del cañón
	BarrelMuzzleLocation->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}