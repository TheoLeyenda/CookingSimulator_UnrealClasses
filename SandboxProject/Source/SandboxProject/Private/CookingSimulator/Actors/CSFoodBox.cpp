#include "CookingSimulator/Actors/CSFoodBox.h"
#include "CookingSimulator/Actors/CSFoodItem.h"
#include "CookingSimulator/Actors/CSGrabbableActor.h"
#include "CookingSimulator/Assets/DataAssets/CSFoodItemDefinition.h"
#include "CookingSimulator/Characters/CSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"

void ACSFoodBox::BeginPlay()
{
	Super::BeginPlay();

	UpdateMaterial();
}


void ACSFoodBox::GrabAndDrop(AActor* Interactor)
{
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(PlacedActor)
		{
			if(PlacedActor->CanBeGrabbed(Character))
			{
				Super::GrabAndDrop(Character);
			}
		}
		else if(Character->GetGrabbedActor())
		{
			Super::GrabAndDrop(Character);
		}
		else
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
			ActorSpawnParameters.Instigator = GetInstigator();
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			ACSFoodItem* FoodItem = GetWorld()->SpawnActor<ACSFoodItem>(FoodItemClass, GetActorTransform(), ActorSpawnParameters);
			if(FoodItem)
			{
				FoodItem->bIsSlicable = true;
				FoodItem->GrabAndDrop(Character);
				FoodItem->SetFoodItemDefinition(FoodItemDefinition.Get());
			}
		}
	}
}

void ACSFoodBox::UpdateMaterial()
{
	if(!FoodItemDefinition || !FoodMaterial)
	{
		return;
	}
	
	UMaterialInstanceDynamic* MaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), FoodMaterial.Get());
	MaterialInstanceDynamic->SetTextureParameterValue("Icon", FoodItemDefinition->Icon.Get());

	StaticMeshComponent->SetMaterial(0, MaterialInstanceDynamic);
}

#if WITH_EDITOR
void ACSFoodBox::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.GetPropertyName();

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ACSFoodBox, FoodItemDefinition) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ACSFoodBox, FoodMaterial))
	{
		UpdateMaterial();
	}
}
#endif
