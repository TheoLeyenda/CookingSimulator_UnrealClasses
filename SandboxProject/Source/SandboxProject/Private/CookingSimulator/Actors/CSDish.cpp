#include "CookingSimulator/Actors/CSDish.h"

#include "Components/BoxComponent.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "Kismet/KismetSystemLibrary.h"

ACSDish::ACSDish()
{
	BoxComponent->SetBoxExtent(FVector(40,40, 20));
	StaticMeshComponent->SetRelativeScale3D(FVector(2,2, 0.02));

	FoodPlace = CreateDefaultSubobject<USceneComponent>(TEXT("FoodPlace"));
	FoodPlace->SetupAttachment(StaticMeshComponent.Get());
}

bool ACSDish::HasPlace() const
{
	return FoodItems.Num() < MaxItemsCount;
}

void ACSDish::AddItem(ACSFoodItem* FoodItem)
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

void ACSDish::OnPlaceFoodOnDishDone(){}
