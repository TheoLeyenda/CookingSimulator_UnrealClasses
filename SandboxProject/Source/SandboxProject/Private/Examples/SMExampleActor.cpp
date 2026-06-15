// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/SMExampleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Examples/SBExampleAnalyticsSubsystem.h"
#include "Examples/SBExampleCoinsSubsystem.h"
#include "Examples/SBExampleConfigPlayerSubsystem.h"
#include "Examples/SBExampleHealthComponent.h"
#include "Examples/SBExampleSpawnManagerSubsystem.h"

// Sets default values
ASMExampleActor::ASMExampleActor()
{
	// Indicas si este Actor debe ejecutar el Tick cada frame
	PrimaryActorTick.bCanEverTick = true;

	// Creas el componente visual en el constructor (Explicado en el turno del UObject)
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    
	// Lo defines como el componente raíz (determina la posición del Actor)
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASMExampleActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("¡El Actor ha nacido en el mundo!"));
}

void ASMExampleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Lógica que ocurre cuadro por cuadro (ej. rotar constantemente)
	AddActorLocalRotation(FRotator(0.0f, 50.0f * DeltaTime, 0.0f));
}

