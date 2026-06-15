#include "Examples/SBChestExample.h"

ASBChestExample::ASBChestExample()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASBChestExample::OnInteract(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("*** y la recompenza es.... *Se convierte en mimico*"))
}


