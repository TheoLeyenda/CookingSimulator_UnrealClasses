#include "CookingSimulator/Actors/CSKitchenware.h"

#include "Components/BoxComponent.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Characters/CSCharacter.h"
#include "CookingSimulator/Components/CSFoodStorageComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ACSKitchenware::ACSKitchenware()
{
	BoxComponent->SetBoxExtent(FVector(40,40, 20));
	StaticMeshComponent->SetRelativeScale3D(FVector(0.9f,0.9f, 0.02));

	FoodPlace = CreateDefaultSubobject<USceneComponent>(TEXT("FoodPlace"));
	FoodPlace->SetupAttachment(StaticMeshComponent.Get());

	FoodStorageComponent = CreateDefaultSubobject<UCSFoodStorageComponent>(TEXT("FoodStorageComponent"));
}

bool ACSKitchenware::HasPlace(int32 NewItemsAmount) const
{
	return FoodStorageComponent->HasPlace(NewItemsAmount);
}

bool ACSKitchenware::IsEmpty() const
{
	return GetFoodItems().IsEmpty();
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
				if(TryAddItems(CharacterKitchenware->GetFoodItems()))
				{
					CharacterKitchenware->ClearFoodItems();
				}
				return false;
			}
			if(CharacterKitchenware->TryAddItems(GetFoodItems()))
			{
				ClearFoodItems();
			}
			return false;
		}
	}

	return false;
}

bool ACSKitchenware::TryAddItem(ACSFoodItem* FoodItem)
{
	if(UKismetSystemLibrary::DoesImplementInterface(FoodItem, UCSDishInterface::StaticClass()) && !IsEmpty())
	{
		bool bShouldAddToKitchen;
		bool Added;
		TryAddItemsToComplex(FoodItem, bShouldAddToKitchen, Added);
		if(bShouldAddToKitchen)
		{
			return FoodStorageComponent->TryAddItem(FoodItem);
		}
		return false;
	}
	
	if(FoodStorageComponent->TryAddItem(FoodItem))
	{
		AttachFoodItem(FoodItem);
		return true;
	}
	

	return false;
}

bool ACSKitchenware::TryAddItems(TArray<ACSFoodItem*> InFoodItems)
{
	if(FoodStorageComponent->TryAddItems(InFoodItems))
	{
		for (auto Element : InFoodItems)
		{
			AttachFoodItem(Element);
		}
		return true;
	}
	return false;
}

void ACSKitchenware::TryAddItemsToComplex(ACSFoodItem* FoodItem, bool& ShouldAddToKitchen, bool& Added)
{
	if(auto* DishInterface = Cast<ICSDishInterface>(FoodItem))
	{
		if(DishInterface->TryAddItems(GetFoodItems()))
		{
			ClearFoodItems();
			ShouldAddToKitchen = false;
			Added = true;
		}
	}
	ShouldAddToKitchen = false;
	Added = false;
}

void ACSKitchenware::AttachFoodItem(ACSFoodItem* FoodItem)
{
	FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	FoodItem->AttachToComponent(FoodPlace.Get(), AttachmentTransformRules);
	FoodItem->MoveToPlace(FVector::ZeroVector);
}

TArray<ACSFoodItem*>& ACSKitchenware::GetFoodItems() const
{
	return FoodStorageComponent->Items;
}

void ACSKitchenware::ClearFoodItems()
{
	FoodStorageComponent->Items.Empty();
}

void ACSKitchenware::Destroyed()
{
	FoodStorageComponent->DestroyItems();
}
