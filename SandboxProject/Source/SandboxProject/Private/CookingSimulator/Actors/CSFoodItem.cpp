#include "CookingSimulator/Actors/CSFoodItem.h"

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
