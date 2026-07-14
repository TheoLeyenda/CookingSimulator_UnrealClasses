#include "CookingSimulator/Actors/CSBurger.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ACSBurger::ACSBurger()
{
	Top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	Top->SetupAttachment(BoxComponent.Get());
}

bool ACSBurger::TryAddItem(ACSFoodItem* FoodItem)
{
	if(!IsFoodItemAllowed(FoodItem))
	{
		return false;
	}

	if(!Super::TryAddItem(FoodItem))
	{
		return false;
	}

	AttachFoodItem(FoodItem);
	return true;
}

bool ACSBurger::TryAddItems(TArray<ACSFoodItem*> FoodItems)
{
	for (auto Element : FoodItems)
	{
		if(!IsFoodItemAllowed(Element))
		{
			return false;
		}
	}

	if(!Super::TryAddItems(FoodItems))
	{
		return false;
	}

	for (auto Element : FoodItems)
	{
		AttachFoodItem(Element);
	}

	return true;
}

bool ACSBurger::IsFoodItemAllowed(ACSFoodItem* FoodItem)
{
	if(!FoodItem)
	{
		return false;
	}
	
	auto* AllowedFoodItemState = AllowedFoodItems.Find(FoodItem->GetFoodItemDefinition());
	return AllowedFoodItemState && *AllowedFoodItemState == FoodItem->GetState();
}

void ACSBurger::AttachFoodItem(ACSFoodItem* FoodItem)
{
	FoodItem->SetState(ECSFoodItemState::InBurger);
	FoodItem->AttachToComponent(BoxComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	FoodItem->MoveToPlace(FVector(0, 0, Top->GetRelativeLocation().Z + TopOffsetZ));

	FVector Origin;
	FVector BoxExtent;
	float SphereRadius;
	UKismetSystemLibrary::GetComponentBounds(FoodItem->StaticMeshComponent.Get(), Origin, BoxExtent, SphereRadius);

	FVector NewRelativeLocation = Top->GetRelativeLocation();
	NewRelativeLocation.Z = Top->GetRelativeLocation().Z + BoxExtent.Z * 2;
	Top->SetRelativeLocation(NewRelativeLocation);

}