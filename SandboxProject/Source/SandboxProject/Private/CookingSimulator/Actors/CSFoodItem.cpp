#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Actors/CSKitchenware.h"
#include "CookingSimulator/Assets/DataAssets/CSFoodItemDefinition.h"
#include "CookingSimulator/Characters/CSCharacter.h"

void ACSFoodItem::SetState(ECSFoodItemState NewState)
{
	State = NewState;

	SetMeshByState(NewState);
}

void ACSFoodItem::SetMeshByState(ECSFoodItemState NewState)
{
	if(!FoodItemDefinition)
	{
		return;
	}
	
	switch (NewState)
	{
	case ECSFoodItemState::Raw:
		if(auto* Mesh = FoodItemDefinition->DefaultMesh.Get())
		{
			StaticMeshComponent->SetStaticMesh(Mesh);
		}
		break;
	case ECSFoodItemState::Slicing:
		if(auto* Mesh = FoodItemDefinition->HalfSlicedMesh.Get())
		{
			StaticMeshComponent->SetStaticMesh(Mesh);
		}
		break;
	case ECSFoodItemState::Sliced:
		if(auto* Mesh = FoodItemDefinition->SlicedMesh.Get())
		{
			StaticMeshComponent->SetStaticMesh(Mesh);
		}
		break;
	case ECSFoodItemState::Fried:
		if(auto* Mesh = FoodItemDefinition->FriedMesh.Get())
		{
			StaticMeshComponent->SetStaticMesh(Mesh);
		}
		break;
	case ECSFoodItemState::InBurger:
		if(auto* Mesh = FoodItemDefinition->InBurgerMesh.Get())
		{
			StaticMeshComponent->SetStaticMesh(Mesh);
		}
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
	case ECSFoodItemState::Fried:
		StateCondition = false;
		break;
	case ECSFoodItemState::InBurger:
		StateCondition = false;
	}

	return bIsSlicable && StateCondition;
}

bool ACSFoodItem::TryGrab(AActor* Interactor)
{
	if(Super::TryGrab(Interactor))
	{
		return true;
	}
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(auto* DishInterface = Cast<ICSDishInterface>(Character->GetGrabbedActor()))
		{
			return DishInterface->TryAddItem(this);
		}
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
			DishInterface->TryAddItem(this);
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
	SetMeshByState(ECSFoodItemState::Raw);
}

UCSFoodItemDefinition* ACSFoodItem::GetFoodItemDefinition() const
{
	return FoodItemDefinition.Get();
}

ECSFoodItemState ACSFoodItem::GetState() const
{
	return State;
}