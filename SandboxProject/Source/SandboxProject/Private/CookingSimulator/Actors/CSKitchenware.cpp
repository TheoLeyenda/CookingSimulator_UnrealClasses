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

void ACSKitchenware::AddItem(ACSFoodItem* FoodItem)
{
	FoodItems.Add(FoodItem);

	FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	FoodItem->AttachToComponent(FoodPlace.Get(), AttachmentTransformRules);

	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName("OnPlaceFoodOnDishDone");
	LatentActionInfo.Linkage = 0;
	LatentActionInfo.UUID = 1;

	UKismetSystemLibrary::MoveComponentTo(
		FoodItem->GetRootComponent(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		false,
		false,
		0.2f,
		false,
		EMoveComponentAction::Type::Move,
		LatentActionInfo);
}

void ACSKitchenware::OnPlaceFoodOnDishDone(){}

bool ACSKitchenware::CanBeGrabbed(ACSCharacter* Character) const
{
	if(!Character)
	{
		return false;
	}
	
	if(!Character->GetGrabbedActor())
	{
		return true;
	}

	if(auto* FoodItem = Cast<ACSFoodItem>(Character->GetGrabbedActor()))
	{
		return HasPlace();
	}

	return false;
}

void ACSKitchenware::AddFoodFromCharacter(ACSCharacter* Character)
{
	if(!Character)
	{
		return;
	}
	
	if(auto* GrabbedActor = Character->GetGrabbedActor())
	{
		if(auto* FoodItem = Cast<ACSFoodItem>(GrabbedActor))
		{
			AddItem(FoodItem);
		}
	}
}

void ACSKitchenware::Grab(ACSCharacter* Character)
{
	AddFoodFromCharacter(Character);
	Super::Grab(Character);
}
