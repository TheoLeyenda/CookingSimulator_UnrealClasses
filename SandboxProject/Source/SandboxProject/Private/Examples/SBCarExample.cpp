#include "Examples/SBCarExample.h"

ASBCarExample::ASBCarExample()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASBCarExample::OnInteract(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("*** Cambio de pawn, rum rum... arranco el auto!"))
}
