#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Actors/CSDish.h"
#include "CookingSimulator/Characters/CSCharacter.h"

void ACSFoodItem::SetState(ECSFoodItemState NewState)
{
	State = NewState;

	switch (State)
	{
	case ECSFoodItemState::Raw:
		StaticMeshComponent->SetMaterial(0, RawMat.Get());
		break;
	case ECSFoodItemState::Slicing:
		StaticMeshComponent->SetMaterial(0, SlicingMat.Get());
		break;
	case ECSFoodItemState::Sliced:
		StaticMeshComponent->SetMaterial(0, SlicedMat.Get());
		break;
	}
}

bool ACSFoodItem::CanBeSliced()
{
	bool StateCondition = false;
	switch (State)
	{
	case ECSFoodItemState::Raw:
		StateCondition = true;
		break;
	case ECSFoodItemState::Slicing:
		StateCondition = true;
		break;
	case ECSFoodItemState::Sliced:
		StateCondition = false;
		break;
	}

	return bIsSlicable && StateCondition;
}

bool ACSFoodItem::CanBeGrabbed(ACSCharacter* Character) const
{
	if(!Character)
	{
		return false;
	}
	
	AActor* GrabbedActor = Character->GetGrabbedActor();
	if(!GrabbedActor)
	{
		return true;
	}

	if(auto* Dish = Cast<ACSDish>(GrabbedActor))
	{
		return Dish->HasPlace();
	}
	
	return false;
}

void ACSFoodItem::Grab(ACSCharacter* Character)
{
	if(!Character)
	{
		return;
	}
	
	DisablePhysics();
	if(auto* GrabbedActor = Character->GetGrabbedActor())
	{
		if(auto* DishInterface = Cast<ICSDishInterface>(GrabbedActor))
		{
			DishInterface->AddItem(this);
		}
	}
	else
	{
		Character->Grab(this);
	}
}
