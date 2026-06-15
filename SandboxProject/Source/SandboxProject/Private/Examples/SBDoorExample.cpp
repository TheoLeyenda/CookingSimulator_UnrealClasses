#include "Examples/SBDoorExample.h"

ASBDoorExample::ASBDoorExample()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASBDoorExample::OnInteract(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("*** Puerta abierta!"))
}
