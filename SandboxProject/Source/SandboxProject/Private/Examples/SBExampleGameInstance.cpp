// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/SBExampleGameInstance.h"

void USBExampleGameInstance::Init()
{
	Super::Init();
	GlobalScore = 0; // Inicialización al arrancar el juego
	UE_LOG(LogTemp, Warning, TEXT("¡Game Instance Inicializado!"));
}

void USBExampleGameInstance::Shutdown()
{
	// Código de limpieza o guardado final aquí
	Super::Shutdown();
}

