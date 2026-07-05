#include "CookingSimulator/Actors/CSKitchenware.h"

#include "Components/BoxComponent.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Characters/CSCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

ACSKitchenware::ACSKitchenware()
{
	BoxComponent->SetBoxExtent(FVector(40,40, 20));
	StaticMeshComponent->SetRelativeScale3D(FVector(0.9f,0.9f, 0.02));

	FoodPlace = CreateDefaultSubobject<USceneComponent>(TEXT("FoodPlace"));
	FoodPlace->SetupAttachment(StaticMeshComponent.Get());
}

bool ACSKitchenware::HasPlace() const
{
	return FoodItems.Num() < MaxItemsCount;
}

bool ACSKitchenware::IsEmpty() const
{
	return FoodItems.IsEmpty();
}

bool ACSKitchenware::TryAddItem(ACSFoodItem* FoodItem)
{
	if(HasPlace())
	{
		FoodItems.Add(FoodItem);

		FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
		FoodItem->AttachToComponent(FoodPlace.Get(), AttachmentTransformRules);
		FoodItem->MoveToPlace();
		return true;
	}

	return false;
}

bool ACSKitchenware::TryGrab(AActor* Interactor)
{
	if(Super::TryGrab(Interactor))
	{
		return true;
	}

	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(auto* FoodItem = Cast<ACSFoodItem>(Character->GetGrabbedActor()))
		{
			if(TryAddItem(FoodItem))
			{
				Grab(Character);
				return true;
			}
		}
		else if(auto* CharacterKitchenware = Cast<ACSKitchenware>(Character->GetGrabbedActor()))
		{
			if(IsEmpty())
			{
				if(TryAddItems(CharacterKitchenware->FoodItems))
				{
					CharacterKitchenware->FoodItems.Empty();
				}
				return false;
			}
			if(CharacterKitchenware->TryAddItems(FoodItems))
			{
				FoodItems.Empty();
			}
			return false;
		}
	}

	return false;
}

bool ACSKitchenware::TryAddItems(TArray<ACSFoodItem*> InFoodItems)
{
	if(InFoodItems.Num() <= MaxItemsCount - FoodItems.Num())
	{
		for (auto Element : InFoodItems)
		{
			TryAddItem(Element);
		}
		return true;
	}
	return false;
}

void ACSKitchenware::Destroyed()
{
	for (auto Item : FoodItems)
	{
		Item->Destroy();
	}
	FoodItems.Empty();
}
