#include "CookingSimulator/Actors/CSOrderPickUpArea.h"
#include "CookingSimulator/Actors/CSPlate.h"
#include "CookingSimulator/Actors/CSPlateBox.h"
#include "CookingSimulator/Characters/CSCharacter.h"
#include "Kismet/GameplayStatics.h"

ACSOrderPickUpArea::ACSOrderPickUpArea()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent.Get());
}

void ACSOrderPickUpArea::BeginPlay()
{
	Super::BeginPlay();

	if(!ConnectedPlateBox)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlateBoxClass, OutActors);

		for (auto Element : OutActors)
		{
			AllPlateBoxes.Add(Cast<ACSPlateBox>(Element));
		}
	}
}

void ACSOrderPickUpArea::GrabAndDrop(AActor* Interactor)
{
	if(auto* Character = Cast<ACSCharacter>(Interactor))
	{
		if(auto* Plate = Cast<ACSPlate>(Character->GetGrabbedActor()))
		{
			if(!Plate->IsEmpty())
			{
				for (auto Element : RecipesForTest)
				{
					if(Element->Compare(Plate->GetIngredients()))
					{
						UE_LOG(LogTemp, Warning, TEXT("*** Has Ingredients (YES)"))
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("*** Hasn't Ingredients (NO)"))
					}
				}
				Plate->Destroy();
				Character->SetGrabbedActor(nullptr);
				if(auto* PlateBox = GetCurrentPlateBox())
				{
					PlateBox->AddPlate();
				}
			}
		}
	}
}

ACSPlateBox* ACSOrderPickUpArea::GetCurrentPlateBox() const
{
	if(ConnectedPlateBox)
	{
		return ConnectedPlateBox.Get();
	}

	int32 ConnectedPlateIndex = FMath::RandRange(0, AllPlateBoxes.Num() - 1);
	return AllPlateBoxes[ConnectedPlateIndex];
}

