#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Actors/CSKitchenware.h"
#include "CookingSimulator/Assets/DataAssets/CSFoodItemDefinition.h"
#include "CookingSimulator/Characters/CSCharacter.h"

void ACSFoodItem::SetState(ECSFoodItemState NewState)
{
	State = NewState;

	if(!FoodItemDefinition)
	{
		return;
	}
	
	switch (State)
	{
	case ECSFoodItemState::Raw:
		StaticMeshComponent->SetStaticMesh(FoodItemDefinition->DefaultMesh.Get());
		break;
	case ECSFoodItemState::Slicing:
		StaticMeshComponent->SetStaticMesh(FoodItemDefinition->HalfSlicedMesh.Get());
		break;
	case ECSFoodItemState::Sliced:
		StaticMeshComponent->SetStaticMesh(FoodItemDefinition->SlicedMesh.Get());
		break;
	case ECSFoodItemState::OnPlate:
		StaticMeshComponent->SetStaticMesh(FoodItemDefinition->OnPlateMesh.Get());
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
	case ECSFoodItemState::OnPlate:
		StateCondition = false;
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

	if(auto* Dish = Cast<ACSKitchenware>(GrabbedActor))
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

void ACSFoodItem::SetFoodItemDefinition(UCSFoodItemDefinition* InFoodItemDefinition)
{
	FoodItemDefinition = InFoodItemDefinition;
	StaticMeshComponent->SetStaticMesh(FoodItemDefinition ? FoodItemDefinition->DefaultMesh.Get() : nullptr);
}

