#include "CookingSimulator/Actors/CSTableWithSlicingPlace.h"

#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Characters/CSCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ACSTableWithSlicingPlace::ACSTableWithSlicingPlace()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void ACSTableWithSlicingPlace::GrabAndDrop(AActor* Interactor)
{
	if(CanGrabActor())
	{
		Super::GrabAndDrop(Interactor);
		Progress = 0;
	}
}

void ACSTableWithSlicingPlace::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(bIsInteracting)
	{
		Progress = UKismetMathLibrary::FInterpTo_Constant(Progress, 1, DeltaSeconds, SlicingSpeed);
		if(Progress == 1)
		{
			StopInteraction(CurrentInteractor.Get());
			if(auto* FoodItem = Cast<ACSFoodItem>(PlacedActor))
			{
				FoodItem->SetState(ECSFoodItemState::Sliced);
			}
		}

		if(bShowProgress)
		{
			UE_LOG(LogTemp, Warning, TEXT("*** Current progress: %f"), Progress);
		}
	}
}

void ACSTableWithSlicingPlace::Interact(AActor* Interactor)
{
	Super::Interact(Interactor);
	
	if(auto* FoodItem = Cast<ACSFoodItem>(PlacedActor))
	{
		if(FoodItem->CanBeSliced())
		{
			FoodItem->SetState(ECSFoodItemState::Slicing);

			if(auto* Character = Cast<ACSCharacter>(Interactor))
			{
				Character->SetIsInteracting(true, this);
				CurrentInteractor = Interactor;
				bIsInteracting = true;
			}
		}
	}
}

void ACSTableWithSlicingPlace::StopInteraction(AActor* Interactor)
{
	Super::StopInteraction(Interactor);
	
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		Character->SetIsInteracting(false, nullptr);
	}

	bIsInteracting = false;
	CurrentInteractor = nullptr;
}